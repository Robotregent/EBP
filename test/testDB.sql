-- phpMyAdmin SQL Dump
-- version 3.4.5deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 23. Mrz 2012 um 22:34
-- Server Version: 5.1.61
-- PHP-Version: 5.3.6-13ubuntu3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `testDB`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Abwesenheit`
--

CREATE TABLE IF NOT EXISTS `Abwesenheit` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `tag` date DEFAULT NULL,
  `grund` text,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Bewohner`
--

CREATE TABLE IF NOT EXISTS `Bewohner` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nummer` bigint(20) unsigned NOT NULL,
  `name` text,
  `geburtsdatum` date DEFAULT NULL,
  `krankenkasse` text,
  `email` text,
  `telefon` text,
  `wohngruppe` bigint(20) unsigned DEFAULT NULL,
  `bezugsbetreuer` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `nummer` (`nummer`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Daten für Tabelle `Bewohner`
--

INSERT INTO `Bewohner` (`id`, `nummer`, `name`, `geburtsdatum`, `krankenkasse`, `email`, `telefon`, `wohngruppe`, `bezugsbetreuer`) VALUES
(1, 1, 'Erster TestBewohner', '2012-03-01', ' AOK', 'erster@test.de ', ' 0123', 1, 1),
(2, 2, 'Zweiter TestBewohner', '2012-03-11', 'BKK', 'zweiter@test.de', ' 555', 1, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Bewohnerereignis`
--

CREATE TABLE IF NOT EXISTS `Bewohnerereignis` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `zeitpunkt` datetime DEFAULT NULL,
  `text` text,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Daten für Tabelle `Bewohnerereignis`
--

INSERT INTO `Bewohnerereignis` (`id`, `zeitpunkt`, `text`, `bewohner`) VALUES
(1, '2012-03-01 18:36:36', 'Heftiger Sturz', 1),
(2, '2012-03-15 00:00:00', 'Aufgewacht', 2);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Bewohnerereignis_schreiber`
--

CREATE TABLE IF NOT EXISTS `Bewohnerereignis_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Bewohnerereignis_schreiber_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Mitarbeiter`
--

CREATE TABLE IF NOT EXISTS `Mitarbeiter` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(128) NOT NULL,
  `berechtigung` enum('AdminRecht','WohnverbundRecht','WohnheimRecht','WohngruppenRecht') NOT NULL,
  `name` text,
  `email` text,
  `telefon` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `login` (`login`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Mitarbeiter`
--

INSERT INTO `Mitarbeiter` (`id`, `login`, `berechtigung`, `name`, `email`, `telefon`) VALUES
(1, 'testUser', 'AdminRecht', 'DerTestUser', 'test@test.de', '012345');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Projekt`
--

CREATE TABLE IF NOT EXISTS `Projekt` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  `beschreibung` text,
  `typ` text,
  `beginn` date DEFAULT NULL,
  `ende` date DEFAULT NULL,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Projekt`
--

INSERT INTO `Projekt` (`id`, `name`, `beschreibung`, `typ`, `beginn`, `ende`, `bewohner`) VALUES
(1, 'testProjekt', 'Ganz viele Tests', 'TestProjektTyp', '2012-03-04', '2012-03-31', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Projekt_verantwortliche`
--

CREATE TABLE IF NOT EXISTS `Projekt_verantwortliche` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Projekt_verantwortliche_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll`
--

CREATE TABLE IF NOT EXISTS `Protokoll` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `inhalt` text,
  `datum` date DEFAULT NULL,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Protokoll`
--

INSERT INTO `Protokoll` (`id`, `inhalt`, `datum`, `bewohner`) VALUES
(1, 'Ganz Viel TestText', '2012-03-04', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll_schreiber`
--

CREATE TABLE IF NOT EXISTS `Protokoll_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Protokoll_schreiber_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll_teilnehmer`
--

CREATE TABLE IF NOT EXISTS `Protokoll_teilnehmer` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Protokoll_teilnehmer_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppe`
--

CREATE TABLE IF NOT EXISTS `Wohngruppe` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  `wohnheim` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Daten für Tabelle `Wohngruppe`
--

INSERT INTO `Wohngruppe` (`id`, `name`, `wohnheim`) VALUES
(1, 'TestGruppe1', NULL),
(2, 'TestGruppe2', NULL);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppenereignis`
--

CREATE TABLE IF NOT EXISTS `Wohngruppenereignis` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `zeitpunkt` datetime DEFAULT NULL,
  `text` text,
  `wohngruppe` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Wohngruppenereignis`
--

INSERT INTO `Wohngruppenereignis` (`id`, `zeitpunkt`, `text`, `wohngruppe`) VALUES
(1, '2012-03-01 00:00:00', 'Alle aufgewacht', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppenereignis_schreiber`
--

CREATE TABLE IF NOT EXISTS `Wohngruppenereignis_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Wohngruppenereignis_schreiber_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppe_mitarbeiter`
--

CREATE TABLE IF NOT EXISTS `Wohngruppe_mitarbeiter` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Wohngruppe_mitarbeiter_object_id` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Wohngruppe_mitarbeiter`
--

INSERT INTO `Wohngruppe_mitarbeiter` (`object_id`, `value`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohnheim`
--

CREATE TABLE IF NOT EXISTS `Wohnheim` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
