-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 29. Apr 2012 um 23:30
-- Server Version: 5.5.22
-- PHP-Version: 5.3.10-1ubuntu3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `ebp_prod`
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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Abwesenheit`
--

INSERT INTO `Abwesenheit` (`id`, `tag`, `grund`, `bewohner`) VALUES
(1, '2012-04-29', 'Elternurlaub', 2);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Betreuung`
--

CREATE TABLE IF NOT EXISTS `Betreuung` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `vorname` text,
  `nachname` text,
  `verein` text,
  `strasse` text,
  `plz` text,
  `ort` text,
  `telefon` text,
  `fax` text,
  `email` text,
  `gesundheitsfuersorge` tinyint(1) NOT NULL,
  `vermoegensfuersorge` tinyint(1) NOT NULL,
  `aufenthaltsbestimmung` tinyint(1) NOT NULL,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

--
-- Daten für Tabelle `Betreuung`
--

INSERT INTO `Betreuung` (`id`, `vorname`, `nachname`, `verein`, `strasse`, `plz`, `ort`, `telefon`, `fax`, `email`, `gesundheitsfuersorge`, `vermoegensfuersorge`, `aufenthaltsbestimmung`, `bewohner`) VALUES
(1, 'Marlene', 'Friedrich', 'SocialCare', 'Charlottenweg 12', '88055', 'Friedrichshafen', '07541/123333', '', 'Friedrich@SocialCare.de', 1, 0, 0, 1),
(2, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 2),
(3, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 3),
(4, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 4),
(5, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 5),
(6, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 6),
(7, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 7),
(8, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 8);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Bewohner`
--

CREATE TABLE IF NOT EXISTS `Bewohner` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `nummer` bigint(20) unsigned NOT NULL,
  `anrede` text,
  `vorname` text,
  `nachname` text,
  `geburtsort` text,
  `geburtsdatum` date DEFAULT NULL,
  `email` text,
  `telefon` text,
  `familienstatus` text,
  `konfession` text,
  `staat` text,
  `seit` date DEFAULT NULL,
  `anmerkung` text,
  `wohngruppe` bigint(20) unsigned DEFAULT NULL,
  `bezugsbetreuer` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `nummer` (`nummer`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

--
-- Daten für Tabelle `Bewohner`
--

INSERT INTO `Bewohner` (`id`, `nummer`, `anrede`, `vorname`, `nachname`, `geburtsort`, `geburtsdatum`, `email`, `telefon`, `familienstatus`, `konfession`, `staat`, `seit`, `anmerkung`, `wohngruppe`, `bezugsbetreuer`) VALUES
(1, 1, 'Herr', 'Johann', 'MÃ¼ller', 'Tettnang', '1956-01-11', NULL, NULL, 'ledig', 'rk', 'deutsch', '2009-10-28', '\n\n', 3, 1),
(2, 2, NULL, 'Manuel', 'Hirsch', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 3, 1),
(3, 3, NULL, 'Frank', 'Schmid', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 3, NULL),
(4, 4, '', 'Helmut', 'Winkel', 'Tettnang', '2000-01-01', NULL, NULL, '', '', '', '2012-04-29', '\n', 4, 2),
(5, 5, NULL, 'Erwin', 'Maier', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 4, NULL),
(6, 6, NULL, 'Sigfried', 'May', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 4, 3),
(7, 7, NULL, 'Herbert', 'Schuster', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 6, NULL),
(8, 8, NULL, 'Herman', 'Hinz', NULL, NULL, NULL, NULL, NULL, NULL, NULL, '2012-04-29', NULL, 4, 3);

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
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Bewohnerereignis_schreiber`
--

CREATE TABLE IF NOT EXISTS `Bewohnerereignis_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Bewohnerereignis_schreiber_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Dokumentation`
--

CREATE TABLE IF NOT EXISTS `Dokumentation` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `typ` enum('einkaufen','waeschepflege','koerperpflege','aufstehenUndZuBettgehen','partnerschaften','freundschaften') NOT NULL,
  `einstufung` enum('bekommeKeineHilfe','bekommeBeratung','bekommeAssistenz','machtMitarbeiter','istWichtig','willLernen') NOT NULL,
  `beschreibung` text,
  `erlaeuterungen` text,
  `ziele` text,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=49 ;

--
-- Daten für Tabelle `Dokumentation`
--

INSERT INTO `Dokumentation` (`id`, `typ`, `einstufung`, `beschreibung`, `erlaeuterungen`, `ziele`, `bewohner`) VALUES
(1, 'einkaufen', 'machtMitarbeiter', NULL, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Siehe Projekt &quot;Einkaufen gehen&quot;</p></body></html>', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">SelbstÃ¤ndig einkaufen gehen lernen.</p></body></html>', 1),
(2, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 1),
(3, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 1),
(4, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Sun April 29 12 Texttransfer aus Gruppenbuch, Eintrag vom Tue Jan 17 07:00:00 2012:</p>\n<p style=" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Johann ist nicht aufgestanden und zu spÃ¤t zur Arbeit gekommen.</p></body></html>', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">PÃ¼nktlich zur Arbeit gehen.</p></body></html>', 1),
(5, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 1),
(6, 'freundschaften', 'istWichtig', NULL, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style="-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><br /></p></body></html>', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Ich mÃ¶chte nicht mehr so hÃ¤ufig meine Freunde durch mein impulsives Auftreten verunsichern.</p></body></html>', 1),
(7, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(8, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(9, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(10, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(11, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(12, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 2),
(13, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(14, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(15, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(16, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(17, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(18, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 3),
(19, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(20, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(21, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(22, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(23, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(24, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 4),
(25, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(26, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(27, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(28, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(29, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(30, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 5),
(31, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(32, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(33, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(34, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(35, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(36, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 6),
(37, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(38, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(39, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(40, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(41, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(42, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 7),
(43, 'einkaufen', 'bekommeKeineHilfe', NULL, NULL, NULL, 8),
(44, 'waeschepflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 8),
(45, 'koerperpflege', 'bekommeKeineHilfe', NULL, NULL, NULL, 8),
(46, 'aufstehenUndZuBettgehen', 'bekommeKeineHilfe', NULL, NULL, NULL, 8),
(47, 'partnerschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 8),
(48, 'freundschaften', 'bekommeKeineHilfe', NULL, NULL, NULL, 8);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Leistungstraeger`
--

CREATE TABLE IF NOT EXISTS `Leistungstraeger` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  `strasse` text,
  `plz` text,
  `ort` text,
  `ansprechpartner` text,
  `telefon` text,
  `fax` text,
  `email` text,
  `anmerkung` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Leistungstraeger`
--

INSERT INTO `Leistungstraeger` (`id`, `name`, `strasse`, `plz`, `ort`, `ansprechpartner`, `telefon`, `fax`, `email`, `anmerkung`) VALUES
(1, 'Sozialamt Freiburg', 'Jacob-Burckhardt-Str. 1', '79098', 'Freiburg im Breisgau', 'Martin*:*Fleuser', '0761 2010', '', 'Fleuser@Sozialamt-freiburg.de', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style="-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"><br /></p></body></html>');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Leistungstraeger_bewohner`
--

CREATE TABLE IF NOT EXISTS `Leistungstraeger_bewohner` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Leistungstraeger_bewohner_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Leistungstraeger_bewohner`
--

INSERT INTO `Leistungstraeger_bewohner` (`object_id`, `value`) VALUES
(1, 1);

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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Daten für Tabelle `Mitarbeiter`
--

INSERT INTO `Mitarbeiter` (`id`, `login`, `berechtigung`, `name`, `email`, `telefon`) VALUES
(1, 'KlausM', 'WohngruppenRecht', 'Klaus MÃ¼ller', ' ', NULL),
(2, 'MariaS', 'WohngruppenRecht', 'Maria Schreiber', ' ', NULL),
(3, 'MarleneF', 'WohngruppenRecht', 'Marlene Friedrich', ' ', NULL);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Projekt`
--

CREATE TABLE IF NOT EXISTS `Projekt` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  `ziele` text,
  `beschreibung` text,
  `typ` text,
  `beginn` date DEFAULT NULL,
  `ende` date DEFAULT NULL,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Daten für Tabelle `Projekt`
--

INSERT INTO `Projekt` (`id`, `name`, `ziele`, `beschreibung`, `typ`, `beginn`, `ende`, `bewohner`) VALUES
(1, 'Einkaufen gehen', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Lernen selbststÃ¤ndig einkaufen zu gehen.</p>\n<ul style="margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;"><li style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Mit dem Bus in die Stadt fahren</li>\n<li style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">im Lidl die vorher besprochenen Dinge einkaufen</li></ul></body></html>', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Um mehr SelbststÃ¤ndikeit zu erlangen, ist es fÃ¼r Johann wichtig alleine einkaufen gehen zu kÃ¶nnen.</p></body></html>', '', '2012-04-29', '2012-04-29', 1),
(2, 'Kleintierzoo', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">RegelmÃ¤ÃŸig jeden Donnerstag im Kleintierzoo den Ziegenstall ausmisten.</p></body></html>', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Um die Veratwortung fÃ¼r ein eigenes Haustier Ãœbernehmen zu kÃ¶nnen, muss Herr MÃ¼ller die nÃ¤chsten acht Wochen zeigen, dass er regelmÃ¤ÃŸig fÃ¼r die ihm anvertrauten Tiere sorgt.</p></body></html>', '', '2012-04-01', '2012-05-31', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Projekt_verantwortliche`
--

CREATE TABLE IF NOT EXISTS `Projekt_verantwortliche` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Projekt_verantwortliche_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Projekt_verantwortliche`
--

INSERT INTO `Projekt_verantwortliche` (`object_id`, `value`) VALUES
(1, 1),
(2, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll`
--

CREATE TABLE IF NOT EXISTS `Protokoll` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `inhalt` text,
  `datum` datetime DEFAULT NULL,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Protokoll`
--

INSERT INTO `Protokoll` (`id`, `inhalt`, `datum`, `bewohner`) VALUES
(1, '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Soll nicht mit Essen werfen</p></body></html>', '2012-04-29 00:00:00', 8);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll_schreiber`
--

CREATE TABLE IF NOT EXISTS `Protokoll_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Protokoll_schreiber_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Protokoll_schreiber`
--

INSERT INTO `Protokoll_schreiber` (`object_id`, `value`) VALUES
(1, 3);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Protokoll_teilnehmer`
--

CREATE TABLE IF NOT EXISTS `Protokoll_teilnehmer` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Protokoll_teilnehmer_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Protokoll_teilnehmer`
--

INSERT INTO `Protokoll_teilnehmer` (`object_id`, `value`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Verfuegung`
--

CREATE TABLE IF NOT EXISTS `Verfuegung` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `aktiv` tinyint(1) NOT NULL,
  `typ` enum('Fixierung','Bettgitter','Psychopharmaka','Patientenverfuegung') NOT NULL,
  `gerichtsbescheid` date DEFAULT NULL,
  `grund` text,
  `bewohner` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Daten für Tabelle `Verfuegung`
--

INSERT INTO `Verfuegung` (`id`, `aktiv`, `typ`, `gerichtsbescheid`, `grund`, `bewohner`) VALUES
(1, 1, 'Fixierung', '2012-11-01', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">SelbstgefÃ¤hrdung</p></body></html>', 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppe`
--

CREATE TABLE IF NOT EXISTS `Wohngruppe` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  `wohnheim` bigint(20) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=7 ;

--
-- Daten für Tabelle `Wohngruppe`
--

INSERT INTO `Wohngruppe` (`id`, `name`, `wohnheim`) VALUES
(3, 'Lukas 10', NULL),
(4, 'Lukas 11', NULL),
(5, 'Lukas 20', NULL),
(6, 'Lukas 21', NULL);

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
(1, '2012-01-17 07:00:00', '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0//EN" "http://www.w3.org/TR/REC-html40/strict.dtd">\n<html><head><meta name="qrichtext" content="1" /><style type="text/css">\np, li { white-space: pre-wrap; }\n</style></head><body style=" font-family:''Ubuntu''; font-size:11pt; font-weight:400; font-style:normal;">\n<p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">Johann ist nicht aufgestanden und zu spÃ¤t zur Arbeit gekommen.</p></body></html>', 3);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppenereignis_schreiber`
--

CREATE TABLE IF NOT EXISTS `Wohngruppenereignis_schreiber` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Wohngruppenereignis_schreiber_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Wohngruppenereignis_schreiber`
--

INSERT INTO `Wohngruppenereignis_schreiber` (`object_id`, `value`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohngruppe_mitarbeiter`
--

CREATE TABLE IF NOT EXISTS `Wohngruppe_mitarbeiter` (
  `object_id` bigint(20) unsigned NOT NULL,
  `value` bigint(20) unsigned DEFAULT NULL,
  KEY `Wohngruppe_mitarbeiter_object_id_i` (`object_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Wohngruppe_mitarbeiter`
--

INSERT INTO `Wohngruppe_mitarbeiter` (`object_id`, `value`) VALUES
(3, 1),
(3, 2),
(3, 3),
(4, 1),
(4, 2),
(4, 3);

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Wohnheim`
--

CREATE TABLE IF NOT EXISTS `Wohnheim` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `name` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `Bewohnerereignis_schreiber`
--
ALTER TABLE `Bewohnerereignis_schreiber`
  ADD CONSTRAINT `Bewohnerereignis_schreiber_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Bewohnerereignis` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Leistungstraeger_bewohner`
--
ALTER TABLE `Leistungstraeger_bewohner`
  ADD CONSTRAINT `Leistungstraeger_bewohner_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Leistungstraeger` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Projekt_verantwortliche`
--
ALTER TABLE `Projekt_verantwortliche`
  ADD CONSTRAINT `Projekt_verantwortliche_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Projekt` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Protokoll_schreiber`
--
ALTER TABLE `Protokoll_schreiber`
  ADD CONSTRAINT `Protokoll_schreiber_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Protokoll` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Protokoll_teilnehmer`
--
ALTER TABLE `Protokoll_teilnehmer`
  ADD CONSTRAINT `Protokoll_teilnehmer_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Protokoll` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Wohngruppenereignis_schreiber`
--
ALTER TABLE `Wohngruppenereignis_schreiber`
  ADD CONSTRAINT `Wohngruppenereignis_schreiber_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Wohngruppenereignis` (`id`) ON DELETE CASCADE;

--
-- Constraints der Tabelle `Wohngruppe_mitarbeiter`
--
ALTER TABLE `Wohngruppe_mitarbeiter`
  ADD CONSTRAINT `Wohngruppe_mitarbeiter_object_id_fk` FOREIGN KEY (`object_id`) REFERENCES `Wohngruppe` (`id`) ON DELETE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
