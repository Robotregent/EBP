#ifndef WOHNGRUPPE_HXX
#define WOHNGRUPPE_HXX


#include <QString>
#include <QSharedPointer>

#include <odb/core.hxx>


namespace drkv
{
	#pragma db object
	class Wohngruppe
	{
		public:
			Wohngruppe( const QString & name )
				: name_(name)
			{
			}

			const QString & name() const { return name_; }
			void name( QString name ) { name_ = name; }

		private:
			Wohngruppe() {}
			friend class odb::access;

			#pragma db id auto
			unsigned long id_;

			QString name_;
	};
}


#endif // WOHNGRUPPE_HXX
