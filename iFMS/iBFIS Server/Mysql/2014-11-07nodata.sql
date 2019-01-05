-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.1.49-community


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema ibfisdata
--

CREATE DATABASE IF NOT EXISTS ibfisdata;
USE ibfisdata;

--
-- Definition of table `branchinfo`
--

DROP TABLE IF EXISTS `branchinfo`;
CREATE TABLE `branchinfo` (
  `BranchId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'SOCç³»ç»Ÿçš„icmsSignä¸€è‡´',
  `Name` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'åç§°',
  `Address` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'åœ°å€',
  `Contact` varchar(20) COLLATE utf8_bin DEFAULT NULL COMMENT 'è”ç³»äºº',
  `Phone` varchar(20) COLLATE utf8_bin DEFAULT NULL COMMENT 'è”ç³»ç”µè¯',
  `Content` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'å¤‡æ³¨',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`BranchId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='æ”¯è¡Œä¿¡æ¯è¡¨';

--
-- Dumping data for table `branchinfo`
--

/*!40000 ALTER TABLE `branchinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `branchinfo` ENABLE KEYS */;


--
-- Definition of table `businessfileinfo`
--

DROP TABLE IF EXISTS `businessfileinfo`;
CREATE TABLE `businessfileinfo` (
  `RecordId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `BusinessInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'ä¸šåŠ¡ä¿¡æ¯ID',
  `Type` int(11) DEFAULT NULL COMMENT 'type=1è¡¨ç¤ºvodï¼Œtype=2è¡¨ç¤ºaudioï¼Œtype=3å¯èƒ½è¡¨ç¤ºå­—æ¯',
  `FileId` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ–‡ä»¶ID',
  `RecordBegin` datetime NOT NULL COMMENT 'å½•åƒå¼€å§‹æ—¶é—´',
  `RecordEnd` datetime NOT NULL COMMENT 'å½•åƒç»“æŸæ—¶é—´',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`RecordId`),
  KEY `FK_BusinessFIleInfo` (`BusinessInfoId`),
  CONSTRAINT `FK_BusinessFIleInfo` FOREIGN KEY (`BusinessInfoId`) REFERENCES `businessinfo` (`BusInessInfoId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ä¸šåŠ¡æ–‡ä»¶ä¿¡æ¯è¡¨';

--
-- Dumping data for table `businessfileinfo`
--

/*!40000 ALTER TABLE `businessfileinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `businessfileinfo` ENABLE KEYS */;


--
-- Definition of table `businessinfo`
--

DROP TABLE IF EXISTS `businessinfo`;
CREATE TABLE `businessinfo` (
  `BusInessInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `Datetime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'ä¸šåŠ¡åŠžç†æ—¶é—´',
  `BranchId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'æ”¯è¡ŒID',
  `ClientId` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'å®¢æˆ·ID',
  `EmployeeId` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ“ä½œå‘˜ID',
  `ProduceId` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'äº§å“ID',
  `SubEquipmentId` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'è®¾å¤‡å”¯ä¸€ç¼–å·',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  `SubEquipmentIcmSign` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Â¼ÏñÉè±¸ËùÊôÏµÍ³ID',
  PRIMARY KEY (`BusInessInfoId`),
  KEY `FK_BranchId_BusIness` (`BranchId`),
  KEY `FK_ClientId` (`ClientId`),
  KEY `FK_EmployeeId_BusIness` (`EmployeeId`),
  KEY `FK_ProduceId` (`ProduceId`),
  CONSTRAINT `FK_BranchId_BusIness` FOREIGN KEY (`BranchId`) REFERENCES `branchinfo` (`BranchId`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `FK_ClientId` FOREIGN KEY (`ClientId`) REFERENCES `clientinfo` (`ClientId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_EmployeeId_BusIness` FOREIGN KEY (`EmployeeId`) REFERENCES `employeeinfo` (`EmployeeId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_ProduceId` FOREIGN KEY (`ProduceId`) REFERENCES `produceinfo` (`ProduceId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ä¸šåŠ¡ä¿¡æ¯è¡¨';

--
-- Dumping data for table `businessinfo`
--

/*!40000 ALTER TABLE `businessinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `businessinfo` ENABLE KEYS */;


--
-- Definition of table `businessrelateinfo`
--

DROP TABLE IF EXISTS `businessrelateinfo`;
CREATE TABLE `businessrelateinfo` (
  `BusinessRelateInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `BusinessInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'ä¸šåŠ¡ID',
  `RelateType` int(20) NOT NULL COMMENT 'è®¾å¤‡ç±»åž‹',
  `Relate1` varchar(100) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‘„åƒæœºç¼–ç  =1 è¡¨ç¤ºæ‘„åƒæœº',
  `Relate2` varchar(100) COLLATE utf8_bin DEFAULT NULL COMMENT 'icmssign',
  `Relate3` longtext COLLATE utf8_bin COMMENT 'icmssignsubequipmentid',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`BusinessRelateInfoId`),
  KEY `FK_BusinessInfoId` (`BusinessInfoId`),
  CONSTRAINT `FK_BusinessInfoId` FOREIGN KEY (`BusinessInfoId`) REFERENCES `businessinfo` (`BusInessInfoId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ä¸šåŠ¡å…³è”è®¾å¤‡è¡¨';

--
-- Dumping data for table `businessrelateinfo`
--

/*!40000 ALTER TABLE `businessrelateinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `businessrelateinfo` ENABLE KEYS */;


--
-- Definition of table `clientinfo`
--

DROP TABLE IF EXISTS `clientinfo`;
CREATE TABLE `clientinfo` (
  `ClientId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `Name` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'å§“å',
  `Credenitial` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'èº«ä»½è¯å·ï¼ˆå”¯ä¸€çº¦æŸï¼‰',
  `Phone` varchar(20) COLLATE utf8_bin DEFAULT NULL COMMENT 'è”ç³»ç”µè¯',
  `Content` varchar(20) COLLATE utf8_bin DEFAULT NULL COMMENT 'å¤‡æ³¨',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`ClientId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='å®¢æˆ·ä¿¡æ¯è¡¨';

--
-- Dumping data for table `clientinfo`
--

/*!40000 ALTER TABLE `clientinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `clientinfo` ENABLE KEYS */;


--
-- Definition of table `employeeinfo`
--

DROP TABLE IF EXISTS `employeeinfo`;
CREATE TABLE `employeeinfo` (
  `EmployeeId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `BranchId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'æ”¯è¡ŒID',
  `Name` varchar(255) COLLATE utf8_bin NOT NULL COMMENT 'å§“å',
  `Password` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'å§“å',
  `CardId` varchar(128) COLLATE utf8_bin NOT NULL COMMENT 'å‘˜å·¥å¡ç¼–å·',
  `RoleId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'è§’è‰²',
  `Phone` varchar(20) COLLATE utf8_bin DEFAULT NULL COMMENT 'è”ç³»ç”µè¯',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`EmployeeId`),
  KEY `FK_BranchId` (`BranchId`),
  KEY `FK_RoleId` (`RoleId`),
  CONSTRAINT `FK_BranchId_Employee` FOREIGN KEY (`BranchId`) REFERENCES `branchinfo` (`BranchId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_RoleId_Employee` FOREIGN KEY (`RoleId`) REFERENCES `roleinfo` (`RoleInfoId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ç”¨æˆ·ä¿¡æ¯è¡¨';

--
-- Dumping data for table `employeeinfo`
--

/*!40000 ALTER TABLE `employeeinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeeinfo` ENABLE KEYS */;


--
-- Definition of table `employeepurview`
--

DROP TABLE IF EXISTS `employeepurview`;
CREATE TABLE `employeepurview` (
  `EmployeePurviewID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `EmployeeId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'è§’è‰²ID',
  `PurviewInfoID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'æƒé™ID',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`EmployeePurviewID`),
  KEY `FK_EmployeeId` (`EmployeeId`),
  KEY `FK_PurviewInfoID` (`PurviewInfoID`),
  CONSTRAINT `FK_EmployeeId` FOREIGN KEY (`EmployeeId`) REFERENCES `employeeinfo` (`EmployeeId`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_PurviewInfoID_Employee` FOREIGN KEY (`PurviewInfoID`) REFERENCES `purviewinfo` (`PurviewInfoID`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ç”¨æˆ·æƒé™è¡¨';

--
-- Dumping data for table `employeepurview`
--

/*!40000 ALTER TABLE `employeepurview` DISABLE KEYS */;
/*!40000 ALTER TABLE `employeepurview` ENABLE KEYS */;


--
-- Definition of table `keyvaleinfo`
--

DROP TABLE IF EXISTS `keyvaleinfo`;
CREATE TABLE `keyvaleinfo` (
  `KeyValeInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `Type` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'ç±»åž‹',
  `Code` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'ç¼–ç ',
  `Value` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'å€¼',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`KeyValeInfoId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ç³»ç»Ÿé…ç½®è¡¨';

--
-- Dumping data for table `keyvaleinfo`
--

/*!40000 ALTER TABLE `keyvaleinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `keyvaleinfo` ENABLE KEYS */;


--
-- Definition of table `produceinfo`
--

DROP TABLE IF EXISTS `produceinfo`;
CREATE TABLE `produceinfo` (
  `ProduceId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `Name` varchar(100) COLLATE utf8_bin NOT NULL,
  `ProduceCode` varchar(100) COLLATE utf8_bin NOT NULL,
  `Period` int(11) DEFAULT NULL,
  `Revenue` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'å‚è€ƒå¹´æ”¶ç›Šï¼šæ”¶ç›ŠçŽ‡',
  `MiniAmount` int(11) DEFAULT NULL COMMENT 'æœ€å°é‡‘é¢ï¼šå…ƒ',
  `RiskLevel` varchar(60) COLLATE utf8_bin DEFAULT NULL COMMENT 'é£Žé™©åå¥½ç­‰çº§',
  `SerialNumber` varchar(100) COLLATE utf8_bin DEFAULT NULL,
  `PublishBeginTime` datetime DEFAULT NULL,
  `PublishEndTime` datetime DEFAULT NULL,
  `ProductionType` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `ApplicableCustomer` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `RevenueType` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `IncrementMoney` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `CurrencyType` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `SealsBranch` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `RevenueInitialDay` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `Deadline` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `PaymentDay` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `TrusteeFee` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `CommissionCharge` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  `Trustee` varchar(100) COLLATE utf8_bin DEFAULT NULL,
  `OverheadCharge` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `RevenueCalculation` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `Content` varchar(1000) COLLATE utf8_bin DEFAULT NULL,
  `MaxTime` int(11) NOT NULL COMMENT 'æœ€å¤§æ—¶é—´:ç§’',
  `MimiTime` int(11) NOT NULL COMMENT 'æœ€å°æ—¶é—´:ç§’',
  `StandardTime` int(11) NOT NULL COMMENT 'æ ‡å‡†æ—¶é—´:ç§’',
  `Prequestion` longtext COLLATE utf8_bin COMMENT 'é¢„è®¾é—®é¢˜',
  `IsPublished` int(11) DEFAULT '0',
  `IsEnabled` int(11) DEFAULT '0',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`ProduceId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='äº§å“ä¿¡æ¯è¡¨';

--
-- Dumping data for table `produceinfo`
--

/*!40000 ALTER TABLE `produceinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `produceinfo` ENABLE KEYS */;


--
-- Definition of table `purviewinfo`
--

DROP TABLE IF EXISTS `purviewinfo`;
CREATE TABLE `purviewinfo` (
  `PurviewInfoID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `ParentPurviewID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'çˆ¶çº§æƒé™IDï¼Œæš‚ä¸º-1',
  `PurviewCode` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'æƒé™ç¼–ç ',
  `Description` varchar(128) COLLATE utf8_bin DEFAULT NULL COMMENT 'æè¿°',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`PurviewInfoID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='æƒé™è¡¨';

--
-- Dumping data for table `purviewinfo`
--

/*!40000 ALTER TABLE `purviewinfo` DISABLE KEYS */;
INSERT INTO `purviewinfo` (`PurviewInfoID`,`ParentPurviewID`,`PurviewCode`,`Description`,`ExtendedInfo1`,`ExtendedInfo2`,`RowVersion`,`SyncVersion`) VALUES 
 (0x35303964663538622D353432382D343138382D383834322D303961646639393135393130,0x35303964663538622D353432382D343138382D383834322D303961646639393135393130,0x3130303035,0xE7B3BBE7BB9FE9858DE7BDAE,NULL,NULL,'2014-10-20 14:17:36','0000-00-00 00:00:00'),
 (0x35393338396639622D613866332D343739312D383536662D386436393936636261363063,0x35393338396639622D613866332D343739312D383536662D386436393936636261363063,0x3130303030,0xE4B89AE58AA1E58A9EE79086,'','','2014-05-30 17:03:18','0000-00-00 00:00:00'),
 (0x36386533653631302D643865652D343137382D623661362D383535613965323631636439,0x36386533653631302D643865652D343137382D623661362D383535613965323631636439,0x3130303031,0xE4B89AE58AA1E69FA5E8AFA2,'','','2014-05-30 17:06:04','0000-00-00 00:00:00'),
 (0x37363438383536392D383531652D346236322D623936662D306661633434323162373534,0x37363438383536392D383531652D346236322D623936662D306661633434323162373534,0x3130303032,0xE4BAA7E59381E7AEA1E79086,'','','2014-07-10 15:45:04','0000-00-00 00:00:00'),
 (0x38636235386433362D336530632D343933612D613338352D653431363536663233313333,0x38636235386433362D336530632D343933612D613338352D653431363536663233313333,0x3130303033,0xE794A8E688B7E7AEA1E79086,'','','2014-07-10 15:45:04','0000-00-00 00:00:00');
/*!40000 ALTER TABLE `purviewinfo` ENABLE KEYS */;


--
-- Definition of table `roleinfo`
--

DROP TABLE IF EXISTS `roleinfo`;
CREATE TABLE `roleinfo` (
  `RoleInfoId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `Name` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'åç§°',
  `RoleLevel` int(11) NOT NULL,
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  `BranchId` varchar(60) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`RoleInfoId`),
  KEY `FK_roleinfo_branchid` (`BranchId`),
  CONSTRAINT `FK_roleinfo_branchid` FOREIGN KEY (`BranchId`) REFERENCES `branchinfo` (`BranchId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='è§’è‰²ä¿¡æ¯è¡¨';

--
-- Dumping data for table `roleinfo`
--

/*!40000 ALTER TABLE `roleinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `roleinfo` ENABLE KEYS */;


--
-- Definition of table `roleinfopurview`
--

DROP TABLE IF EXISTS `roleinfopurview`;
CREATE TABLE `roleinfopurview` (
  `RoleInfoPurviewID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `RoleId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'è§’è‰²ID',
  `PurviewInfoID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'æƒé™ID',
  `ExtendedInfo` int(11) DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`RoleInfoPurviewID`),
  KEY `FK_RoleId` (`RoleId`),
  KEY `FK_PurviewInfoID` (`PurviewInfoID`),
  CONSTRAINT `FK_PurviewInfoID` FOREIGN KEY (`PurviewInfoID`) REFERENCES `purviewinfo` (`PurviewInfoID`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `FK_RoleId` FOREIGN KEY (`RoleId`) REFERENCES `roleinfo` (`RoleInfoId`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='è§’è‰²æƒé™ä¿¡æ¯è¡¨';

--
-- Dumping data for table `roleinfopurview`
--

/*!40000 ALTER TABLE `roleinfopurview` DISABLE KEYS */;
/*!40000 ALTER TABLE `roleinfopurview` ENABLE KEYS */;


--
-- Definition of table `uermapinfo`
--

DROP TABLE IF EXISTS `uermapinfo`;
CREATE TABLE `uermapinfo` (
  `UerMapInfoID` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Guidå…¨å±€å”¯ä¸€',
  `EmployeeId` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'ç”¨æˆ·GUID',
  `SocUserName` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Socç”¨æˆ·å',
  `SocUserPassWord` varchar(60) COLLATE utf8_bin NOT NULL COMMENT 'Socç™»å½•å¯†ç ',
  `ExtendedInfo1` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `ExtendedInfo2` varchar(2000) COLLATE utf8_bin DEFAULT NULL COMMENT 'æ‰©å±•å­—æ®µ',
  `RowVersion` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'å½“å‰æ—¶é—´æˆ³',
  `SyncVersion` timestamp NULL DEFAULT '0000-00-00 00:00:00' COMMENT 'åŒæ­¥æ—¶é—´æˆ³',
  PRIMARY KEY (`UerMapInfoID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='ç”¨æˆ·æ˜ å°„è¡¨';

--
-- Dumping data for table `uermapinfo`
--

/*!40000 ALTER TABLE `uermapinfo` DISABLE KEYS */;
/*!40000 ALTER TABLE `uermapinfo` ENABLE KEYS */;


--
-- Definition of procedure `proc_branchinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_branchinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_branchinfo_insert`(iBranchId VARCHAR(60)
,iName VARCHAR(60)
,iAddress VARCHAR(60)
,iContact VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
)
BEGIN
  set @sqlCount = 'select count(branchid) from branchinfo where
      branchid = iBranchid';
  if @sqlCount = 0
  then
        insert into branchinfo(
                BranchId,
                Name,
                Address,
                Contact,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        )
        values(
                iBranchId,
                iName,
                iAddress,
                iContact,
                iPhone,
                iContent,
                iExtendedInfo,
                iExtendedInfo1,
                iExtendedInfo2
        );
  elseif @sqlCount = 1
  then
        update branchinfo
        set Name=iName
          ,Address=iAddress
          ,Contact=iContact
          ,Phone=iPhone
          ,Content=iContent
          ,ExtendedInfo=iExtendedInfo
          ,ExtendedInfo1=iExtendedInfo1
          ,ExtendedInfo2=iExtendedInfo2
        where BranchId= iBranchId;
  end if;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_branchinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_branchinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_branchinfo_select`()
BEGIN
        select BranchId,
                Name,
                Address,
                Contact,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from branchinfo;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_branchinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_branchinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_branchinfo_selectbyid`(iBranchId VARCHAR(60))
BEGIN
        select BranchId,
                Name,
                Address,
                Contact,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from branchinfo
        where branchinfo.BranchId=iBranchId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_branchinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_branchinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_branchinfo_update`(iBranchId VARCHAR(60)
,iName VARCHAR(60)
,iAddress VARCHAR(60)
,iContact VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN
      update branchinfo
      set Name=iName
          ,Address=iAddress
          ,Contact=iContact
          ,Phone=iPhone
          ,Content=iContent
          ,ExtendedInfo=iExtendedInfo
          ,ExtendedInfo1=iExtendedInfo1
          ,ExtendedInfo2=iExtendedInfo2
      where BranchId=iBranchId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessfileinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_businessfileinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessfileinfo_insert`(
iRecordId VARCHAR(60)
,iBusinessInfoId VARCHAR(60)
,iType INT(11)
,iFileId  VARCHAR(60)
,iRecordBegin DATETIME
,iRecordEnd DATETIME
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN
        insert into businessfileinfo(RecordId
        ,BusinessInfoId
        ,`Type`
        ,FileId
        ,RecordBegin
        ,RecordEnd
        ,ExtendedInfo
        ,ExtendedInfo1
        ,ExtendedInfo2)
        values(iRecordId,iBusinessInfoId,iType,iFileId,iRecordBegin,iRecordEnd,iExtendedInfo,iExtendedInfo1,iExtendedInfo2);
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessfileinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_businessfileinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessfileinfo_select`()
BEGIN
        select   RecordId,
                 BusinessInfoId,
                 `Type`,
                 FileId,
                 RecordBegin,
                 RecordEnd,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2
        from businessfileinfo;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessfileinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_businessfileinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessfileinfo_selectbyid`(
iRecordId VARCHAR(60))
BEGIN
        select   RecordId,
                 BusinessInfoId,
                 `Type`,
                 FileId,
                 RecordBegin,
                 RecordEnd,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2
        from businessfileinfo
        where RecordId=iRecordId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessfileinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_businessfileinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessfileinfo_update`(
iRecordId VARCHAR(60)
,iBusinessInfoId VARCHAR(60)
,iType INT(11)
,iFileId  VARCHAR(60)
,iRecordBegin DATETIME
,iRecordEnd DATETIME
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
)
BEGIN
        update businessfileinfo set
	        BusinessInfoId=iBusinessInfoId
	        ,`Type`=iType
	        ,FileId=iFileId
	        ,RecordBegin=iRecordBegin
	        ,RecordEnd=iRecordEnd
	        ,ExtendedInfo=iExtendedInfo
	        ,ExtendedInfo1=iExtendedInfo1
	        ,ExtendedInfo2=iExtendedInfo2
        where RecordId=iRecordId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_count_querybycondition`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_count_querybycondition`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_count_querybycondition`( iBranchId varchar(60)
,iEmployeeId varchar(60)
,iCustomerId varchar(60)
,iProduceId varchar(60)
,iStartTime  datetime
,iEndTime datetime
 )
BEGIN
       set @sqlCount='
       select  count(BusInessInfoId)
       from BusInessInfo
       where ';
       if iBranchId <> '' && iBranchId is not null
       then  set @sqlCount=concat(@sqlCount,' BranchId = \'',iBranchId,'\' and ');
       end if;
       if iEmployeeId <> '' && iEmployeeId is not null
       then  set @sqlCount=concat(@sqlCount,' EmployeeId = \'',iEmployeeId,'\' and ');
       end if;
       if iProduceId <> ''  && iProduceId is not null
       then  set @sqlCount=concat(@sqlCount,' ProduceId = \'',iProduceId,'\' and ');
       end if;
       if iCustomerId <> '' && iCustomerId is not null
       then  set @sqlCount=concat(@sqlCount,' ClientId = \'',iCustomerId,'\' and ');
       end if;
       set @sqlCount=concat(@sqlCount, ' `Datetime` >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and `Datetime` <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');

       prepare strsql  from @sqlCount;
       execute strsql;
       deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_insert`(
iBusInessInfoId VARCHAR(60)
,iDatetime TIMESTAMP
,iBranchId VARCHAR(60)
,iClientId VARCHAR(60)
,iEmployeeId VARCHAR(60)
,iProduceId VARCHAR(60)
,iSubEquipmentId VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
,iSubEquipmentIcmSign VARCHAR(60))
BEGIN
	insert into businessinfo(BusInessInfoId
                                ,`DateTime`
				,BranchId
				,ClientId
				,EmployeeId 
				,ProduceId
				,SubEquipmentId 
				,ExtendedInfo 
				,ExtendedInfo1
				,ExtendedInfo2
				,SubEquipmentIcmSign)

	values(iBusInessInfoId
			,iDatetime
			,iBranchId 
			,iClientId 
			,iEmployeeId 
			,iProduceId
			,iSubEquipmentId 
			,iExtendedInfo 
			,iExtendedInfo1 
			,iExtendedInfo2
			,iSubEquipmentIcmSign);
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_querybycondition`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_querybycondition`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_querybycondition`( iBranchId varchar(60)
,iEmployeeId varchar(60)
,iCustomerId varchar(60)
,iProduceId varchar(60)
,iStartTime  datetime
,iEndTime datetime
,PageSize int
,PageIndex int
 )
BEGIN
       set @sql='
       select * from BusInessInfo
       where ';
       if iBranchId <> '' && iBranchId is not null
       then  set @sql=concat(@sql,' a.BranchId = \'',iBranchId,'\' and ');
       end if;
       if iEmployeeId <> '' && iEmployeeId is not null
       then  set @sql=concat(@sql,' a.EmployeeId = \'',iEmployeeId,'\' and ');
       end if;
       if iProduceId <> ''  && iProduceId is not null
       then  set @sql=concat(@sql,' a.ProduceId = \'',iProduceId,'\' and ');
       end if;
       if iCustomerId <> '' && iCustomerId is not null
       then  set @sql=concat(@sql,' a.ClientId = \'',iCustomerId,'\' and ');
       end if;
       set @sql=concat(@sql, ' `Datetime` >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and `Datetime` <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');
       set @sql=concat(@sql, ' order by `Datetime` desc');
       set @sql=concat(@sql, ' LIMIT ',PageSize * PageIndex,' , ',PageSize);

       prepare strsql  from @sql;
       execute strsql;
       deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_select`()
BEGIN
	select  BusInessInfoId,
                `Datetime`,
                 BranchId,
                 ClientId,
                 EmployeeId,
                 ProduceId,
                 SubEquipmentId,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2,
                 SubEquipmentIcmSign
        from businessinfo; 
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_selectbyid`(
iBusInessInfoId VARCHAR(60))
BEGIN
	select  BusInessInfoId,
                `Datetime`,
                 BranchId,
                 ClientId,
                 EmployeeId,
                 ProduceId,
                 SubEquipmentId,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2,
                 SubEquipmentIcmSign
        from businessinfo where BusInessInfoId=iBusInessInfoId; 
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_businessinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessinfo_update`(iBusInessInfoId VARCHAR(60)
,iDatetime TIMESTAMP
,iBranchId VARCHAR(60)
,iClientId VARCHAR(60)
,iEmployeeId VARCHAR(60)
,iProduceId VARCHAR(60)
,iSubEquipmentId VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
,iSubEquipmentIcmSign VARCHAR(60))
BEGIN
	update businessinfo set `Datetime`=iDatetime
				,BranchId =iBranchId
				,ClientId =iClientId
				,EmployeeId =iEmployeeId
				,ProduceId=iProduceId
				,SubEquipmentId =iSubEquipmentId
				,ExtendedInfo =iExtendedInfo
				,ExtendedInfo1 =iExtendedInfo1
				,ExtendedInfo2=iExtendedInfo2
                                ,SubEquipmentIcmSign=iSubEquipmentIcmSign
	where BusInessInfoId=iBusInessInfoId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businesspagequerybycondition`
--

DROP PROCEDURE IF EXISTS `proc_businesspagequerybycondition`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businesspagequerybycondition`( iBranchId varchar(60)
,iEmployeeId varchar(60)
,iCustomerId varchar(60)
,iProductId varchar(60)
,iStartTime  datetime
,iEndTime datetime
,PageSize int
,PageIndex int
,out RecordCount int
 )
BEGIN
       set @sqlCount='
       select  count(BusInessInfoId) into @RecordCountemp
       from BusInessInfo
       where ';
       if iBranchId <> '' && iBranchId is not null
       then  set @sqlCount=concat(@sqlCount,' BranchId = \'',iBranchId,'\' and ');
       end if;
       if iEmployeeId <> '' && iEmployeeId is not null
       then  set @sqlCount=concat(@sqlCount,' EmployeeId = \'',iEmployeeId,'\' and ');
       end if;
       if iProductId <> ''  && iProductId is not null
       then  set @sqlCount=concat(@sqlCount,' ProduceId = \'',iProductId,'\' and ');
       end if;
       if iCustomerId <> '' && iCustomerId is not null
       then  set @sqlCount=concat(@sqlCount,' ClientId = \'',iCustomerId,'\' and ');
       end if;
       set @sqlCount=concat(@sqlCount, ' `Datetime` >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and `Datetime` <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');

       prepare strsql  from @sqlCount;
       execute strsql;
       deallocate prepare strsql;

       set RecordCount = @RecordCountemp;

       set @sql='
       select  a.BusInessInfoId as BusInessInfoId,
               a.`Datetime` as `Datetime`,
               a.BranchId as BranchId,
               a.ClientId as ClientId,
               a.EmployeeId as EmployeeId,
               a.ProduceId as ProduceId,
               a.SubEquipmentIcmSign as SubEquipmentIcmSign,
               a.SubEquipmentId as SubEquipmentId,
               a.ExtendedInfo  as  BusInessInfo_ExtendedInfo,
               a.ExtendedInfo1  as BusInessInfo_ExtendedInfo1,
               a.ExtendedInfo2  as BusInessInfo_ExtendedInfo2,

               b.Name as BranchInfo_Name,
               b.Address as Address,
               b.Contact as Contact,
               b.Phone as BranchInfo_Phone,
               b.Content as BranchInfo_Content,
               b.ExtendedInfo  as BranchInfo_ExtendedInfo,
               b.ExtendedInfo1  as BranchInfo_ExtendedInfo1,
               b.ExtendedInfo2  as BranchInfo_ExtendedInfo2,

               c.Name  as ClientInfo_Name,
               c.Credenitial  as Credenitial,
               c.Phone  as ClientInfo_Phone,
               c.Content  as ClientInfo_Content,
               c.ExtendedInfo  as ClientInfo_ExtendedInfo,
               c.ExtendedInfo1  as ClientInfo_ExtendedInfo1,
               c.ExtendedInfo2  as ClientInfo_ExtendedInfo2,

               d.Name as EmployeeInfo_Name,
               d.`Password` as `Password`,
               d.CardId as CardId,
               d.RoleId as RoleId,
               d.Phone as EmployeeInfo_Phone,
               d.ExtendedInfo  as EmployeeInfo_ExtendedInfo,
               d.ExtendedInfo1  as EmployeeInfo_ExtendedInfo1,
               d.ExtendedInfo2  as EmployeeInfo_ExtendedInfo2,

               e.Name  as ProduceInfo_Name,
               e.ProduceCode  as ProduceCode,
               e.Period  as Period,
               e.Revenue  as Revenue,
               e.MiniAmount  as MiniAmount,
               e.RiskLevel  as RiskLevel,
               e.MaxTime as MaxTime,
               e.MimiTime as MimiTime,
               e.StandardTime as StandardTime,
               e.Prequestion as Prequestion,
               e.ExtendedInfo  as ProduceInfo_ExtendedInfo,
               e.ExtendedInfo1  as ProduceInfo_ExtendedInfo1,
               e.ExtendedInfo2  as ProduceInfo_ExtendedInfo2,
               e.SerialNumber as SerialNumber,
               e.PublishBeginTime as PublishBeginTime,
               e.ProductionType as ProductionType,
               e.ApplicableCustomer as ApplicableCustomer,
               e.RevenueType as RevenueType,
               e.IncrementMoney as IncrementMoney,
               e.CurrencyType as CurrencyType,
               e.SealsBranch as SealsBranch,
               e.RevenueInitialDay as RevenueInitialDay,
               e.Deadline as Deadline,
               e.PaymentDay as PaymentDay,
               e.TrusteeFee as TrusteeFee,
               e.CommissionCharge as CommissionCharge,
               e.OverheadCharge as OverheadCharge,
               e.RevenueCalculation as RevenueCalculation,
               e.Content as ProduceInfo_Content,
               e.PublishEndTime as PublishEndTime,
               e.IsPublished  as IsPublished,
               e.IsEnabled as IsEnabled,
               e.Trustee as Trustee
       from BusInessInfo a
               left join BranchInfo b
               on a.BranchId=b.BranchId
               left join ClientInfo c
               on a.ClientId=c.ClientId
               left join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               left join ProduceInfo e
               on a.ProduceId=e.ProduceId
       where ';
       if iBranchId <> '' && iBranchId is not null
       then  set @sql=concat(@sql,' a.BranchId = \'',iBranchId,'\' and ');
       end if;
       if iEmployeeId <> '' && iEmployeeId is not null
       then  set @sql=concat(@sql,' a.EmployeeId = \'',iEmployeeId,'\' and ');
       end if;
       if iProductId <> ''  && iProductId is not null
       then  set @sql=concat(@sql,' a.ProduceId = \'',iProductId,'\' and ');
       end if;
       if iCustomerId <> '' && iCustomerId is not null
       then  set @sql=concat(@sql,' a.ClientId = \'',iCustomerId,'\' and ');
       end if;
       set @sql=concat(@sql, ' `Datetime` >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and `Datetime` <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');
       set @sql=concat(@sql, ' order by `Datetime` desc');
       set @sql=concat(@sql, ' LIMIT ',PageSize * PageIndex,' , ',PageSize);

       prepare strsql  from @sql;
       execute strsql;
       deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessquerybycondition`
--

DROP PROCEDURE IF EXISTS `proc_businessquerybycondition`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessquerybycondition`( iBranchId varchar(60)
,iEmployeeId varchar(60)
,iCustomerId varchar(60)
,iProductId varchar(60)
,iStartTime  datetime
,iEndTime datetime
,PageSize int
,PageIndex int
 )
BEGIN
       set @sql='
       select  a.BusInessInfoId as BusInessInfoId,
               a.`Datetime` as `Datetime`,
               a.BranchId as BranchId,
               a.ClientId as ClientId,
               a.EmployeeId as EmployeeId,
               a.ProduceId as ProduceId,
               a.SubEquipmentIcmSign as SubEquipmentIcmSign,
               a.SubEquipmentId as SubEquipmentId,
               a.ExtendedInfo  as  BusInessInfo_ExtendedInfo,
               a.ExtendedInfo1  as BusInessInfo_ExtendedInfo1,
               a.ExtendedInfo2  as BusInessInfo_ExtendedInfo2,

               b.Name as BranchInfo_Name,
               b.Address as Address,
               b.Contact as Contact,
               b.Phone as BranchInfo_Phone,
               b.Content as BranchInfo_Content,
               b.ExtendedInfo  as BranchInfo_ExtendedInfo,
               b.ExtendedInfo1  as BranchInfo_ExtendedInfo1,
               b.ExtendedInfo2  as BranchInfo_ExtendedInfo2,

               c.Name  as ClientInfo_Name,
               c.Credenitial  as Credenitial,
               c.Phone  as ClientInfo_Phone,
               c.Content  as ClientInfo_Content,
               c.ExtendedInfo  as ClientInfo_ExtendedInfo,
               c.ExtendedInfo1  as ClientInfo_ExtendedInfo1,
               c.ExtendedInfo2  as ClientInfo_ExtendedInfo2,

               d.Name as EmployeeInfo_Name,
               d.`Password` as `Password`,
               d.CardId as CardId,
               d.RoleId as RoleId,
               d.Phone as EmployeeInfo_Phone,
               d.ExtendedInfo  as EmployeeInfo_ExtendedInfo,
               d.ExtendedInfo1  as EmployeeInfo_ExtendedInfo1,
               d.ExtendedInfo2  as EmployeeInfo_ExtendedInfo2,

               e.Name  as ProduceInfo_Name,
               e.ProduceCode  as ProduceCode,
               e.Period  as Period,
               e.Revenue  as Revenue,
               e.MiniAmount  as MiniAmount,
               e.RiskLevel  as RiskLevel,
               e.MaxTime as MaxTime,
               e.MimiTime as MimiTime,
               e.StandardTime as StandardTime,
               e.Prequestion as Prequestion,
               e.ExtendedInfo  as ProduceInfo_ExtendedInfo,
               e.ExtendedInfo1  as ProduceInfo_ExtendedInfo1,
               e.ExtendedInfo2  as ProduceInfo_ExtendedInfo2,
               e.SerialNumber as SerialNumber,
               e.PublishBeginTime as PublishBeginTime,
               e.ProductionType as ProductionType,
               e.ApplicableCustomer as ApplicableCustomer,
               e.RevenueType as RevenueType,
               e.IncrementMoney as IncrementMoney,
               e.CurrencyType as CurrencyType,
               e.SealsBranch as SealsBranch,
               e.RevenueInitialDay as RevenueInitialDay,
               e.Deadline as Deadline,
               e.PaymentDay as PaymentDay,
               e.TrusteeFee as TrusteeFee,
               e.CommissionCharge as CommissionCharge,
               e.OverheadCharge as OverheadCharge,
               e.RevenueCalculation as RevenueCalculation,
               e.Content as ProduceInfo_Content,
               e.PublishEndTime as PublishEndTime,
               e.IsPublished  as IsPublished,
               e.IsEnabled as IsEnabled,
               e.Trustee as Trustee,

               f.RecordId as RecordId,
               f.`Type` as `Type`,
               f.FileId as FileId,
               f.RecordBegin as RecordBegin,
               f.RecordEnd as RecordEnd,
               f.ExtendedInfo  as BusinessFIleInfo_ExtendedInfo,
               f.ExtendedInfo1  as BusinessFIleInfo_ExtendedInfo1,
               f.ExtendedInfo2  as BusinessFIleInfo_ExtendedInfo2,

               g.BusinessRelateInfoId as BusinessRelateInfoId,
               g.RelateType as RelateType,
               g.Relate1 as Relate1,
               g.Relate2 as Relate2,
               g.Relate3 as Relate3

       from BusInessInfo a
               left join BranchInfo b
               on a.BranchId=b.BranchId
               left join ClientInfo c
               on a.ClientId=c.ClientId
               left join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               left join ProduceInfo e
               on a.ProduceId=e.ProduceId
               left join BusinessFIleInfo f
               on a.BusInessInfoId=f.BusinessInfoId
               left join  BusinessRelateInfo g
               on a.BusInessInfoId=g.BusinessInfoId
       where ';
       if iBranchId <> null
       then  set @sql=concat(@sql,' BranchId = ',iBranchId,' and ');
       end if;
       if iEmployeeId <> null
       then  set @sql=concat(@sql,' EmployeeId = ',iEmployeeId,' and ');
       end if;
       if iProductId <> null
       then  set @sql=concat(@sql,' ProduceId = ',iProduceId,' and ');
       end if;
       set @sql=concat(@sql, ' Datetime >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and Datetime <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');
       set @sql=concat(@sql,' order by  Datetime ');
	   set @sql=concat(@sql,' LIMIT  ',PageSize*PageIndex,' , ',PageSize);

       prepare strsql  from @sql;
       execute strsql;

       set @sqlCount='
       select  count(a.BusInessInfoId) as RecordCount
       from BusInessInfo a
               left join BranchInfo b
               on a.BranchId=b.BranchId
               left join ClientInfo c
               on a.ClientId=c.ClientId
               left join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               left join ProduceInfo e
               on a.ProduceId=e.ProduceId
               left join BusinessFIleInfo f
               on a.BusInessInfoId=f.BusinessInfoId
               left join  BusinessRelateInfo g
               on a.BusInessInfoId=g.BusinessInfoId
       where ';
       if iBranchId <> null
       then  set @sqlCount=concat(@sqlCount,' BranchId = ',iBranchId,' and ');
       end if;
       if iEmployeeId <> null
       then  set @sqlCount=concat(@sqlCount,' EmployeeId = ',iEmployeeId,' and ');
       end if;
       if iProductId <> null
       then  set @sqlCount=concat(@sqlCount,' ProduceId = ',iProduceId,' and ');
       end if;
       set @sqlCount=concat(@sqlCount, ' Datetime >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and Datetime <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');

       prepare strsql  from @sqlCount;
	   execute strsql;
       deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessquerybyconditiontest2`
--

DROP PROCEDURE IF EXISTS `proc_businessquerybyconditiontest2`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessquerybyconditiontest2`( iBranchId varchar(60)
,iEmployeeId varchar(60)
,iCustomerId varchar(60)
,iProductId varchar(60)
,iStartTime  datetime
,iEndTime datetime
,PageSize int
,PageIndex int
,out Rowcount int
 )
BEGIN
       set @sqlCount='
       select  count(a.BusInessInfoId) into @RecordCount
       from BusInessInfo a
               inner join BranchInfo b
               on a.BranchId=b.BranchId
               inner join ClientInfo c
               on a.ClientId=c.ClientId
               inner join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               inner join ProduceInfo e
               on a.ProduceId=e.ProduceId
               inner join BusinessFIleInfo f
               on a.BusInessInfoId=f.BusinessInfoId
               inner join  BusinessRelateInfo g
               on a.BusInessInfoId=g.BusinessInfoId
       where ';
       if iBranchId <> null
       then  set @sqlCount=concat(@sqlCount,' BranchId = ',iBranchId,' and ');
       end if;
       if iEmployeeId <> null
       then  set @sqlCount=concat(@sqlCount,' EmployeeId = ',iEmployeeId,' and ');
       end if;
       if iProductId <> null
       then  set @sqlCount=concat(@sqlCount,' ProduceId = ',iProduceId,' and ');
       end if;
       set @sqlCount=concat(@sqlCount, ' Datetime >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and Datetime <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');

       prepare strsql  from @sqlCount;
       execute strsql;
       deallocate prepare strsql;

       set Rowcount = @RecordCount;

       set @sql='
       select  a.BusInessInfoId as BusInessInfoId,
               a.`Datetime` as `Datetime`,
               a.BranchId as BranchId,
               a.ClientId as ClientId,
               a.EmployeeId as EmployeeId,
               a.ProduceId as ProduceId,
               a.SubEquipmentIcmSign as SubEquipmentIcmSign,
               a.SubEquipmentId as SubEquipmentId,
               a.ExtendedInfo  as  BusInessInfo_ExtendedInfo,
               a.ExtendedInfo1  as BusInessInfo_ExtendedInfo1,
               a.ExtendedInfo2  as BusInessInfo_ExtendedInfo2,

               b.Name as BranchInfo_Name,
               b.Address as Address,
               b.Contact as Contact,
               b.Phone as BranchInfo_Phone,
               b.Content as BranchInfo_Content,
               b.ExtendedInfo  as BranchInfo_ExtendedInfo,
               b.ExtendedInfo1  as BranchInfo_ExtendedInfo1,
               b.ExtendedInfo2  as BranchInfo_ExtendedInfo2,

               c.Name  as ClientInfo_Name,
               c.Credenitial  as Credenitial,
               c.Phone  as ClientInfo_Phone,
               c.Content  as ClientInfo_Content,
               c.ExtendedInfo  as ClientInfo_ExtendedInfo,
               c.ExtendedInfo1  as ClientInfo_ExtendedInfo1,
               c.ExtendedInfo2  as ClientInfo_ExtendedInfo2,

               d.Name as EmployeeInfo_Name,
               d.`Password` as `Password`,
               d.CardId as CardId,
               d.RoleId as RoleId,
               d.Phone as EmployeeInfo_Phone,
               d.ExtendedInfo  as EmployeeInfo_ExtendedInfo,
               d.ExtendedInfo1  as EmployeeInfo_ExtendedInfo1,
               d.ExtendedInfo2  as EmployeeInfo_ExtendedInfo2,

               e.Name  as ProduceInfo_Name,
               e.ProduceCode  as ProduceCode,
               e.Period  as Period,
               e.Revenue  as Revenue,
               e.MiniAmount  as MiniAmount,
               e.RiskLevel  as RiskLevel,
               e.MaxTime as MaxTime,
               e.MimiTime as MimiTime,
               e.StandardTime as StandardTime,
               e.Prequestion as Prequestion,
               e.ExtendedInfo  as ProduceInfo_ExtendedInfo,
               e.ExtendedInfo1  as ProduceInfo_ExtendedInfo1,
               e.ExtendedInfo2  as ProduceInfo_ExtendedInfo2,
               e.SerialNumber as SerialNumber,
               e.PublishBeginTime as PublishBeginTime,
               e.ProductionType as ProductionType,
               e.ApplicableCustomer as ApplicableCustomer,
               e.RevenueType as RevenueType,
               e.IncrementMoney as IncrementMoney,
               e.CurrencyType as CurrencyType,
               e.SealsBranch as SealsBranch,
               e.RevenueInitialDay as RevenueInitialDay,
               e.Deadline as Deadline,
               e.PaymentDay as PaymentDay,
               e.TrusteeFee as TrusteeFee,
               e.CommissionCharge as CommissionCharge,
               e.OverheadCharge as OverheadCharge,
               e.RevenueCalculation as RevenueCalculation,
               e.Content as ProduceInfo_Content,
               e.PublishEndTime as PublishEndTime,
               e.IsPublished  as IsPublished,
               e.IsEnabled as IsEnabled,
               e.Trustee as Trustee,

               f.RecordId as RecordId,
               f.`Type` as `Type`,
               f.FileId as FileId,
               f.RecordBegin as RecordBegin,
               f.RecordEnd as RecordEnd,
               f.ExtendedInfo  as BusinessFIleInfo_ExtendedInfo,
               f.ExtendedInfo1  as BusinessFIleInfo_ExtendedInfo1,
               f.ExtendedInfo2  as BusinessFIleInfo_ExtendedInfo2,

               g.BusinessRelateInfoId as BusinessRelateInfoId,
               g.RelateType as RelateType,
               g.Relate1 as Relate1,
               g.Relate2 as Relate2,
               g.Relate3 as Relate3

       from BusInessInfo a
               inner join BranchInfo b
               on a.BranchId=b.BranchId
               inner join ClientInfo c
               on a.ClientId=c.ClientId
               inner join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               inner join ProduceInfo e
               on a.ProduceId=e.ProduceId
               inner join BusinessFIleInfo f
               on a.BusInessInfoId=f.BusinessInfoId
               inner join  BusinessRelateInfo g
               on a.BusInessInfoId=g.BusinessInfoId
       where ';
       if iBranchId <> null
       then  set @sql=concat(@sql,' BranchId = ',iBranchId,' and ');
       end if;
       if iEmployeeId <> null
       then  set @sql=concat(@sql,' EmployeeId = ',iEmployeeId,' and ');
       end if;
       if iProductId <> null
       then  set @sql=concat(@sql,' ProduceId = ',iProduceId,' and ');
       end if;
       set @sql=concat(@sql, ' Datetime >= \'',DATE_FORMAT(iStartTime,'%Y-%m-%d %H:%i:%s'),'\' and Datetime <= \'',DATE_FORMAT(iEndTime,'%Y-%m-%d %H:%i:%s'),'\'');
       set @sql=concat(@sql,' order by  Datetime ');
       set @sql=concat(@sql,' LIMIT  ',PageSize*PageIndex,' , ',PageSize);

       prepare strsql  from @sql;
       execute strsql;
       deallocate prepare strsql;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessrelateinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_businessrelateinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessrelateinfo_insert`(
iBusinessRelateInfoId VARCHAR(60)
,iBusinessInfoId VARCHAR(60)
,iRelateType INT(20)
,iRelate1 VARCHAR(100)
,iRelate2 VARCHAR(100)
,iRelate3 LONGTEXT )
BEGIN

	insert into businessrelateinfo(BusinessRelateInfoId
			,BusinessInfoId
			,RelateType
			,Relate1
			,Relate2
			,Relate3)
	values(iBusinessRelateInfoId
			,iBusinessInfoId
			,iRelateType
			,iRelate1
			,iRelate2
			,iRelate3);
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessrelateinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_businessrelateinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessrelateinfo_select`()
BEGIN
	select BusinessRelateInfoId,
                BusinessInfoId,
                RelateType,
                Relate1,
                Relate2,
                Relate3
	from businessrelateinfo;   
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessrelateinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_businessrelateinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessrelateinfo_selectbyid`(
iBusinessRelateInfoId VARCHAR(60))
BEGIN
	select BusinessRelateInfoId,
                BusinessInfoId,
                RelateType,
                Relate1,
                Relate2,
                Relate3
	from businessrelateinfo
	where BusinessRelateInfoId=iBusinessRelateInfoId;   
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_businessrelateinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_businessrelateinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_businessrelateinfo_update`(iBusinessRelateInfoId VARCHAR(60)
,iBusinessInfoId VARCHAR(60)
,iRelateType INT(20)
,iRelate1 VARCHAR(100)
,iRelate2 VARCHAR(100)
,iRelate3 LONGTEXT)
BEGIN
	update businessrelateinfo
	set BusinessInfoId=iBusinessInfoId
            ,RelateType=iRelateType
            ,Relate1=iRelate1
            ,Relate2=iRelate2
            ,Relate3=iRelate3
	where BusinessRelateInfoId=iBusinessRelateInfoId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_changepassword`
--

DROP PROCEDURE IF EXISTS `proc_changepassword`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_changepassword`(iEmployeeId	VARCHAR(60)
	, iPassword	VARCHAR(60)
	, OUT isok 	INT )
BEGIN

	UPDATE EmployeeInfo SET `Password` = iPassword WHERE EmployeeId= iEmployeeId ;
	IF @@error_count <> 0
	THEN SET isok = -1;
	ELSE SET isok = 1;
	END IF;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfosynctime_select`
--

DROP PROCEDURE IF EXISTS `proc_clientinfosynctime_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfosynctime_select`()
BEGIN
        select max(RowVersion) from clientinfo;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_insert`(inout iClientId VARCHAR(60)
,iName VARCHAR(60)
,iCredenitial VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN
	declare tmpID varchar(60) default '';
	select ClientID into tmpID from ClientInfo 
	where Credenitial = iCredenitial;

	if (tmpID != '') then
		set iClientID = tmpID;
	else
	insert into ClientInfo (ClientId
			,Name
			,Credenitial
			,Phone
			,Content
			,ExtendedInfo
			,ExtendedInfo1
			,ExtendedInfo2)
	values(iClientId
                 ,iName
                 ,iCredenitial
                 ,iPhone
                 ,iContent
                 ,iExtendedInfo
                 ,iExtendedInfo1
                 ,iExtendedInfo2);
	set iClientID = iClientID;
	end if;
    
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_select`()
BEGIN
        select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from clientinfo;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_selectbycredenitial`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_selectbycredenitial`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_selectbycredenitial`(
iCredenitial VARCHAR(60) )
BEGIN
        select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from clientinfo
	where Credenitial=iCredenitial;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_selectbyempleeid`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_selectbyempleeid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_selectbyempleeid`(
iempleeid VARCHAR(60),branchid VARCHAR(60) )
BEGIN    
        select distinct clientinfo.ClientId,
                clientinfo.Name,
                clientinfo.Credenitial,
                clientinfo.Phone,
                clientinfo.Content,
                clientinfo.ExtendedInfo,
                clientinfo.ExtendedInfo1,
                clientinfo.ExtendedInfo2
	from clientinfo,businessinfo
	where clientinfo.ClientId=businessinfo.ClientId and(businessinfo.BranchId=branchid||branchid="") and (businessinfo.EmployeeId=iempleeid ||iempleeid="");
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_selectbyid`(
iClientId VARCHAR(60) )
BEGIN
        select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from clientinfo
	where ClientId=iClientId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_selecttosync`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_selecttosync`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_selecttosync`(iRowVersion DATETIME)
BEGIN
  select * from ClientInfo where RowVersion > iRowVersion;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_update`(iClientId VARCHAR(60)
,iName VARCHAR(60)
,iCredenitial VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN
        declare num1 int default -1;
        declare num2 int default -1;

        select  count(*) into num1 from ClientInfo where Credenitial=iCredenitial;
        select  count(*) into num2 from ClientInfo where Credenitial=iCredenitial and ClientId=iClientId;

        if num1=1 and num2=0
        then set num1=1;
        else
	        update clientinfo set Name=iName
			,Credenitial=iCredenitial
			,Phone=iPhone
			,Content=iContent
			,ExtendedInfo =iExtendedInfo
			,ExtendedInfo1=iExtendedInfo1
			,ExtendedInfo2=iExtendedInfo2
        	where ClientId=iClientId;
        end if;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_clientinfo_updatebycredenitial`
--

DROP PROCEDURE IF EXISTS `proc_clientinfo_updatebycredenitial`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_clientinfo_updatebycredenitial`(iClientId VARCHAR(60)
,iName VARCHAR(60)
,iCredenitial VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN

	update clientinfo set ClientId=iClientId
      ,Name=iName
			,Credenitial=iCredenitial
			,Phone=iPhone
			,Content=iContent
			,ExtendedInfo =iExtendedInfo
			,ExtendedInfo1=iExtendedInfo1
			,ExtendedInfo2=iExtendedInfo2
	where Credenitial=iCredenitial;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_deleterolepurviews`
--

DROP PROCEDURE IF EXISTS `proc_deleterolepurviews`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_deleterolepurviews`(iRoleId varchar(60))
BEGIN
      delete from RoleInfoPurview where  RoleId = iRoleId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_deleteuserpurviews`
--

DROP PROCEDURE IF EXISTS `proc_deleteuserpurviews`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_deleteuserpurviews`(iEmployeeId varchar(60))
BEGIN
      delete from EmployeePurview where  EmployeeId = iEmployeeId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeeinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_employeeinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeeinfo_insert`( iEmployeeId VARCHAR(60)
, iBranchId	VARCHAR(60)
, iName	    VARCHAR(255)
, iPassword	VARCHAR(60)
, iCardId	  VARCHAR(128)
, iRoleId	  VARCHAR(60)
, iPhone		VARCHAR(20)
, iExtendedInfo 	INT(11)
, iExtendedInfo1	VARCHAR(2000)
, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	INSERT INTO EmployeeInfo (EmployeeId,BranchId,Name,`Password`,CardId,RoleId,Phone,ExtendedInfo ,ExtendedInfo1,ExtendedInfo2)
        VALUES 			(iEmployeeId,iBranchId,iName,iPassword,iCardId,iRoleId,iPhone,iExtendedInfo ,iExtendedInfo1,iExtendedInfo2);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeeinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_employeeinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeeinfo_select`()
BEGIN

	SELECT  EmployeeId,
                BranchId,
                Name,
                `Password`,
                CardId,
                RoleId,
                Phone,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        FROM EmployeeInfo;  
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeeinfo_selectbybranchid`
--

DROP PROCEDURE IF EXISTS `proc_employeeinfo_selectbybranchid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeeinfo_selectbybranchid`( pBranchId VARCHAR(60)
	 )
BEGIN

	          select  EmployeeId 	as     EmployeeId,
					BranchId    as     BranchId,
					Name        as     EmployeeInfo_Name,
					Password  as     Password,
					CardId         as     CardId ,
					RoleId 	as     RoleId ,
					Phone    	as     EmployeeInfo_Phone ,
					ExtendedInfo     as    EmployeeInfo_ExtendedInfo ,
					ExtendedInfo1    as    EmployeeInfo_ExtendedInfo1 ,
					ExtendedInfo2    as    EmployeeInfo_ExtendedInfo2 
              from employeeinfo
					where BranchId = pBranchId or pBranchId="";  
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeeinfo_selectbyemployeeid`
--

DROP PROCEDURE IF EXISTS `proc_employeeinfo_selectbyemployeeid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeeinfo_selectbyemployeeid`( iEmployeeId VARCHAR(60)
	 )
BEGIN

	SELECT  EmployeeId,
                BranchId,
                Name,
                `Password`,
                CardId,
                RoleId,
                Phone,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        FROM EmployeeInfo WHERE EmployeeId = iEmployeeId ;  
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeeinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_employeeinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeeinfo_update`( iEmployeeId VARCHAR(60)
	, iBranchId    	 VARCHAR(60)
	, iName		 VARCHAR(255)
	, iPassword	     VARCHAR(60)
	, iCardId	       VARCHAR(128)
	, iRoleId	       VARCHAR(60)
	, iPhone		VARCHAR(20)
	, iExtendedInfo 	INT(11)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	UPDATE EmployeeInfo SET BranchId = iBranchId
	, Name = iName
	, `Password` = iPassword
	, CardId = iCardId
	, RoleId = iRoleId
	, Phone = iPhone
	, ExtendedInfo = iExtendedInfo
	, ExtendedInfo1 = iExtendedInfo1
	, ExtendedInfo2 = iExtendedInfo2
	WHERE EmployeeId = iEmployeeId ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeepurview_deletebyemployeeid`
--

DROP PROCEDURE IF EXISTS `proc_employeepurview_deletebyemployeeid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeepurview_deletebyemployeeid`(iEmployeeId varchar(60))
BEGIN
  delete from EmployeePurview where EmployeeId=iEmployeeId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeepurview_insert`
--

DROP PROCEDURE IF EXISTS `proc_employeepurview_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeepurview_insert`( iEmployeePurviewID VARCHAR(60)
	, iEmployeeId		VARCHAR(60)
	, iPurviewInfoID	VARCHAR(60)
	, iExtendedInfo 	INT(11)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	INSERT INTO EmployeePurview (EmployeePurviewID,EmployeeId,PurviewInfoID,ExtendedInfo ,ExtendedInfo1,ExtendedInfo2)
        VALUES 		(iEmployeePurviewID,iEmployeeId,iPurviewInfoID,iExtendedInfo ,iExtendedInfo1,iExtendedInfo2);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeepurview_select`
--

DROP PROCEDURE IF EXISTS `proc_employeepurview_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeepurview_select`()
BEGIN

	SELECT   EmployeePurviewID,
                 EmployeeId,
                 PurviewInfoID,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2
        FROM EmployeePurview;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeepurview_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_employeepurview_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeepurview_selectbyid`( iEmployeePurviewID VARCHAR(60)
	 )
BEGIN

	SELECT   EmployeePurviewID,
                 EmployeeId,
                 PurviewInfoID,
                 ExtendedInfo,
                 ExtendedInfo1,
                 ExtendedInfo2
        FROM EmployeePurview WHERE EmployeePurviewID = iEmployeePurviewID ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_employeepurview_update`
--

DROP PROCEDURE IF EXISTS `proc_employeepurview_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_employeepurview_update`( iEmployeePurviewID VARCHAR(60)
	, iEmployeeId	   VARCHAR(60)
	, iPurviewInfoID	VARCHAR(60)
	, iExtendedInfo 	INT(11)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	UPDATE EmployeePurview SET EmployeeId = iEmployeeId
	, PurviewInfoID = iPurviewInfoID
	, ExtendedInfo = iExtendedInfo
	, ExtendedInfo1 = iExtendedInfo1
	, ExtendedInfo2 = iExtendedInfo2
	WHERE EmployeePurviewID = iEmployeePurviewID ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getallproducetinfo`
--

DROP PROCEDURE IF EXISTS `proc_getallproducetinfo`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getallproducetinfo`()
BEGIN
       select ProduceId,
                       Name,
                       ProduceCode,
                       Period,
                       Revenue,
                       MiniAmount,
                       RiskLevel,
                       MaxTime,
                       MimiTime,
                       StandardTime,
                       Prequestion,
                       ExtendedInfo,
                       ExtendedInfo1,
                       ExtendedInfo2
       from ProduceInfo;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getallroleallpurview`
--

DROP PROCEDURE IF EXISTS `proc_getallroleallpurview`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getallroleallpurview`()
BEGIN
  select
			a.RoleInfoId    as   RoleInfoId ,
			a.Name          as   Name ,
			a.RoleLevel     as   RoleLevel ,
			a.ExtendedInfo  as   RoleInfo_ExtendedInfo ,
			a.ExtendedInfo1 as   RoleInfo_ExtendedInfo1 ,
			a.ExtendedInfo2 as   RoleInfo_ExtendedInfo2 ,

			b.RoleInfoPurviewID  as    RoleInfoPurviewID ,
			
			
			b.ExtendedInfo       as    RoleInfoPurview_ExtendedInfo ,
			b.ExtendedInfo1      as    RoleInfoPurview_ExtendedInfo1 ,
			b.ExtendedInfo2      as    RoleInfoPurview_ExtendedInfo2 ,

			c.PurviewInfoID      as    PurviewInfoID ,
			c.ParentPurviewID    as    ParentPurviewID ,
			c.PurviewCode        as    PurviewCode,
			c.Description        as    Description,
			c.ExtendedInfo1      as    PurviewInfo_ExtendedInfo1 ,
			c.ExtendedInfo2      as    PurviewInfo_ExtendedInfo2
  from RoleInfo a
		left join RoleInfoPurview  b
		on a.RoleInfoId = b.RoleId
		left join PurviewInfo c
		on  b.PurviewInfoID = c.PurviewInfoID;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getallroleinfo`
--

DROP PROCEDURE IF EXISTS `proc_getallroleinfo`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getallroleinfo`(
iRoleInfoId varchar(60))
BEGIN

          select
			a.RoleInfoId    as   RoleInfoId ,
			a.Name          as   Name ,
			a.RoleLevel     as   RoleLevel ,
			a.ExtendedInfo  as   RoleInfo_ExtendedInfo ,
			a.ExtendedInfo1 as   RoleInfo_ExtendedInfo1 ,
			a.ExtendedInfo2 as   RoleInfo_ExtendedInfo2 ,

			b.RoleInfoPurviewID  as    RoleInfoPurviewID ,

			
			b.ExtendedInfo       as    RoleInfoPurview_ExtendedInfo ,
			b.ExtendedInfo1      as    RoleInfoPurview_ExtendedInfo1 ,
			b.ExtendedInfo2      as    RoleInfoPurview_ExtendedInfo2 ,

			c.PurviewInfoID      as    PurviewInfoID ,
			c.ParentPurviewID    as    ParentPurviewID ,
			c.PurviewCode        as    PurviewCode,
			c.Description        as    Description,
			c.ExtendedInfo1      as    PurviewInfo_ExtendedInfo1 ,
			c.ExtendedInfo2      as    PurviewInfo_ExtendedInfo2
          from RoleInfo a
		left join RoleInfoPurview  b
		on a.RoleInfoId = b.RoleId
		left join PurviewInfo c
		on  b.PurviewInfoID = c.PurviewInfoID
          where   a.RoleInfoId =iRoleInfoId;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getalluserallinfo`
--

DROP PROCEDURE IF EXISTS `proc_getalluserallinfo`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getalluserallinfo`()
BEGIN
          select  a.EmployeeId 	as     EmployeeId,
					a.BranchId    as     BranchId,
					a.Name        as     EmployeeInfo_Name,
					a.`Password`  as     `Password`,
					a.CardId         as     CardId ,
					a.RoleId 	as     RoleId ,
					a.Phone    	as     EmployeeInfo_Phone ,
					a.ExtendedInfo     as    EmployeeInfo_ExtendedInfo ,
					a.ExtendedInfo1    as    EmployeeInfo_ExtendedInfo1 ,
					a.ExtendedInfo2    as    EmployeeInfo_ExtendedInfo2 ,

					b.UerMapInfoID   as    UerMapInfoID ,
					b.SocUserName      as    SocUserName,
					b.SocUserPassWord  as    SocUserPassWord,
					b.ExtendedInfo1   as    UerMapInfo_ExtendedInfo1,
					b.ExtendedInfo2   as    UerMapInfo_ExtendedInfo2,

					c.EmployeePurviewID as  EmployeePurviewID,
					c.PurviewInfoID     as  PurviewInfoID,
					c.ExtendedInfo   as   EmployeePurview_ExtendedInfo ,
					c.ExtendedInfo1  as   EmployeePurview_ExtendedInfo1 ,
					c.ExtendedInfo2  as   EmployeePurview_ExtendedInfo2 ,

					d.Name      as   BranchInfo_Name,
					d.Address   as   Address,
					d.Contact   as   Contact,
					d.Phone     as   BranchInfo_Phone,
					d.Content   as   Content,
					d.ExtendedInfo    as  BranchInfo_ExtendedInfo ,
					d.ExtendedInfo1   as  BranchInfo_ExtendedInfo1 ,
					d.ExtendedInfo2   as  BranchInfo_ExtendedInfo2 ,

					e.PurviewInfoID    as   PurviewInfoID ,
					e.ParentPurviewID  as   ParentPurviewID ,
					e.PurviewCode    as     PurviewCode ,
					e.Description    as     Description ,
					e.ExtendedInfo1  as     ExtendedInfo1 ,
					e.ExtendedInfo2  as     ExtendedInfo2 ,

					f.RoleInfoId   as   RoleInfoId ,
					f.Name         as   RoleInfo_Name ,
					f.RoleLevel    as   RoleLevel,
					f.ExtendedInfo   as   RoleInfo_ExtendedInfo ,
					f.ExtendedInfo1  as   RoleInfo_ExtendedInfo1 ,
					f.ExtendedInfo2  as   RoleInfo_ExtendedInfo2

	from EmployeeInfo a
					left join UerMapInfo b
					on a.EmployeeId = b.EmployeeId
					left join EmployeePurview c
					on a.EmployeeId = c.EmployeeId
					left join BranchInfo d
					on a.BranchId = d.BranchId
					left join PurviewInfo e
					on c.PurviewInfoID = e.PurviewInfoID
					left join RoleInfo f
					on a.RoleId = f.RoleInfoId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getbusinessfIleinfobybusinessinfoid`
--

DROP PROCEDURE IF EXISTS `proc_getbusinessfIleinfobybusinessinfoid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getbusinessfIleinfobybusinessinfoid`(iBusinessInfoId varchar(60))
BEGIN
       select RecordId
        ,BusinessInfoId
        ,`Type`
        ,FileId
        ,RecordBegin
        ,RecordEnd
        ,ExtendedInfo
        ,ExtendedInfo1
        ,ExtendedInfo2
       from BusinessFIleInfo where  BusinessInfoId= iBusinessInfoId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getbusinessinfoall`
--

DROP PROCEDURE IF EXISTS `proc_getbusinessinfoall`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getbusinessinfoall`(IN `iBusInessInfoId` varchar(60))
BEGIN

	SELECT  
			a.BusInessInfoId as BusInessInfoId,
			a.`Datetime` as `Datetime`,
			a.BranchId as BranchId,
			a.ClientId as ClientId,
			a.EmployeeId as EmployeeId,
			a.ProduceId as ProduceId,
			a.SubEquipmentId as SubEquipmentId,
			a.ExtendedInfo  as  BusInessInfo_ExtendedInfo,
			a.ExtendedInfo1 as BusInessInfo_ExtendedInfo1,
			a.ExtendedInfo2 as BusInessInfo_ExtendedInfo2,

			b.BusinessRelateInfoId as BusinessRelateInfoId,
			
			b.RelateType as RelateType,
			b.Relate1 as Relate1,
			b.Relate2 as Relate2,
			b.Relate3 as Relate3,

			c.RecordId as RecordId,
			
			c.`Type` as `Type`,
			c.FileId as FileId,
			c.RecordBegin as RecordBegin,
			c.RecordEnd as RecordEnd,
			c.ExtendedInfo as BusinessFIleInfo_ExtendedInfo,
			c.ExtendedInfo1 as BusinessFIleInfo_ExtendedInfo1,
			c.ExtendedInfo2 as BusinessFIleInfo_ExtendedInfo2
	FROM BusInessInfo a
		LEFT JOIN BusinessRelateInfo b
		ON a.BusInessInfoId =b.BusinessInfoId 
		LEFT JOIN BusinessFIleInfo c
		ON a.BusInessInfoId =c.BusinessInfoId
	WHERE a.BusInessInfoId=iBusInessInfoId;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getbusinessinfoallexp2`
--

DROP PROCEDURE IF EXISTS `proc_getbusinessinfoallexp2`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getbusinessinfoallexp2`(iBusInessInfoId varchar(60)
)
BEGIN
       set @sql='
       select  a.BusInessInfoId as BusInessInfoId,
               a.`Datetime` as `Datetime`,
               a.BranchId as BranchId,
               a.ClientId as ClientId,
               a.EmployeeId as EmployeeId,
               a.ProduceId as ProduceId,
               a.SubEquipmentIcmSign as SubEquipmentIcmSign,
               a.SubEquipmentId as SubEquipmentId,
               a.ExtendedInfo  as  BusInessInfo_ExtendedInfo,
               a.ExtendedInfo1  as BusInessInfo_ExtendedInfo1,
               a.ExtendedInfo2  as BusInessInfo_ExtendedInfo2,

               b.Name as BranchInfo_Name,
               b.Address as Address,
               b.Contact as Contact,
               b.Phone as BranchInfo_Phone,
               b.Content as BranchInfo_Content,
               b.ExtendedInfo  as BranchInfo_ExtendedInfo,
               b.ExtendedInfo1  as BranchInfo_ExtendedInfo1,
               b.ExtendedInfo2  as BranchInfo_ExtendedInfo2,

               c.Name  as ClientInfo_Name,
               c.Credenitial  as Credenitial,
               c.Phone  as ClientInfo_Phone,
               c.Content  as ClientInfo_Content,
               c.ExtendedInfo  as ClientInfo_ExtendedInfo,
               c.ExtendedInfo1  as ClientInfo_ExtendedInfo1,
               c.ExtendedInfo2  as ClientInfo_ExtendedInfo2,

               d.Name as EmployeeInfo_Name,
               d.`Password` as `Password`,
               d.CardId as CardId,
               d.RoleId as RoleId,
               d.Phone as EmployeeInfo_Phone,
               d.ExtendedInfo  as EmployeeInfo_ExtendedInfo,
               d.ExtendedInfo1  as EmployeeInfo_ExtendedInfo1,
               d.ExtendedInfo2  as EmployeeInfo_ExtendedInfo2,

               e.Name  as ProduceInfo_Name,
               e.ProduceCode  as ProduceCode,
               e.Period  as Period,
               e.Revenue  as Revenue,
               e.MiniAmount  as MiniAmount,
               e.RiskLevel  as RiskLevel,
               e.MaxTime as MaxTime,
               e.MimiTime as MimiTime,
               e.StandardTime as StandardTime,
               e.Prequestion as Prequestion,
               e.ExtendedInfo  as ProduceInfo_ExtendedInfo,
               e.ExtendedInfo1  as ProduceInfo_ExtendedInfo1,
               e.ExtendedInfo2  as ProduceInfo_ExtendedInfo2,
               e.SerialNumber as SerialNumber,
               e.PublishBeginTime as PublishBeginTime,
               e.ProductionType as ProductionType,
               e.ApplicableCustomer as ApplicableCustomer,
               e.RevenueType as RevenueType,
               e.IncrementMoney as IncrementMoney,
               e.CurrencyType as CurrencyType,
               e.SealsBranch as SealsBranch,
               e.RevenueInitialDay as RevenueInitialDay,
               e.Deadline as Deadline,
               e.PaymentDay as PaymentDay,
               e.TrusteeFee as TrusteeFee,
               e.CommissionCharge as CommissionCharge,
               e.OverheadCharge as OverheadCharge,
               e.RevenueCalculation as RevenueCalculation,
               e.Content as ProduceInfo_Content,
               e.PublishEndTime as PublishEndTime,
               e.IsPublished  as IsPublished,
               e.IsEnabled as IsEnabled,
               e.Trustee as Trustee,

               f.RecordId as RecordId,
               f.`Type` as `Type`,
               f.FileId as FileId,
               f.RecordBegin as RecordBegin,
               f.RecordEnd as RecordEnd,
               f.ExtendedInfo  as BusinessFIleInfo_ExtendedInfo,
               f.ExtendedInfo1  as BusinessFIleInfo_ExtendedInfo1,
               f.ExtendedInfo2  as BusinessFIleInfo_ExtendedInfo2,

               g.BusinessRelateInfoId as BusinessRelateInfoId,
               g.RelateType as RelateType,
               g.Relate1 as Relate1,
               g.Relate2 as Relate2,
               g.Relate3 as Relate3

       from BusInessInfo a
               inner join BranchInfo b
               on a.BranchId=b.BranchId
               inner join ClientInfo c
               on a.ClientId=c.ClientId
               inner join EmployeeInfo d
               on a.EmployeeId=d.EmployeeId
               inner join ProduceInfo e
               on a.ProduceId=e.ProduceId
               inner join BusinessFIleInfo f
               on a.BusInessInfoId=f.BusinessInfoId
               inner join  BusinessRelateInfo g
               on a.BusInessInfoId=g.BusinessInfoId
       where a.BusInessInfoId ';
       set @sql=concat(@sql,' = \'',iBusInessInfoId,'\'');

       prepare strsql  from @sql;
       execute strsql;
       deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getbusinessrelateinfobybusinessinfoid`
--

DROP PROCEDURE IF EXISTS `proc_getbusinessrelateinfobybusinessinfoid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getbusinessrelateinfobybusinessinfoid`(iBusInessInfoId varchar(60))
BEGIN
       select BusinessRelateInfoId
        ,BusinessInfoId
        ,RelateType
        ,Relate1
        ,Relate2
        ,Relate3
       from   BusinessRelateInfo where BusinessInfoId= iBusInessInfoId;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getcustombyemployee`
--

DROP PROCEDURE IF EXISTS `proc_getcustombyemployee`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getcustombyemployee`(iEmployeeId varchar(60)
)
BEGIN
        if iEmployeeId <> '' && iEmployeeId is not null
        then  select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2 from ClientInfo  where ClientId in(select ClientId from BusInessInfo where EmployeeId= iEmployeeId);
        else  select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2 from ClientInfo  where ClientId in(select ClientId from BusInessInfo);
        end if ;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getcustomerproduce`
--

DROP PROCEDURE IF EXISTS `proc_getcustomerproduce`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getcustomerproduce`(iClientId VARCHAR(60)
)
BEGIN
        IF  iClientId is not null && iClientId <> ''
        THEN    select ProduceId,
                       Name,
                       ProduceCode,
                       Period,
                       Revenue,
                       MiniAmount,
                       RiskLevel,
                       MaxTime,
                       MimiTime,
                       StandardTime,
                       Prequestion,
                       ExtendedInfo,
                       ExtendedInfo1,
                       ExtendedInfo2 from ProduceInfo where ProduceId in(select ProduceId from BusInessInfo where ClientId = iClientId);
        ELSE    select ProduceId,
                       Name,
                       ProduceCode,
                       Period,
                       Revenue,
                       MiniAmount,
                       RiskLevel,
                       MaxTime,
                       MimiTime,
                       StandardTime,
                       Prequestion,
                       ExtendedInfo,
                       ExtendedInfo1,
                       ExtendedInfo2 from ProduceInfo where ProduceId in(select ProduceId from BusInessInfo);
        END IF;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getemployeebybranch`
--

DROP PROCEDURE IF EXISTS `proc_getemployeebybranch`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getemployeebybranch`(iBranchId varchar(60)
)
BEGIN
     if iBranchId is not null &&  iBranchId <>''
     then select EmployeeId,
                BranchId,
                Name,
                `Password`,
                CardId,
                RoleId,
                Phone,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2 from EmployeeInfo where BranchId=iBranchId ;
     else select EmployeeId,
                BranchId,
                Name,
                `Password`,
                CardId,
                RoleId,
                Phone,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2 from EmployeeInfo;
     end if;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getemployeebyroleid`
--

DROP PROCEDURE IF EXISTS `proc_getemployeebyroleid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getemployeebyroleid`(iRoleInfoId VARCHAR(60))
BEGIN
	select  a.EmployeeId 	as     EmployeeId,
					a.BranchId    as     BranchId,
					a.Name        as    EmployeeInfo_Name,
					a.`Password`    as     `Password`,
					a.CardId    	as     CardId ,
					a.RoleId    	as     RoleId ,
					a.Phone    	as     EmployeeInfo_Phone ,
					a.ExtendedInfo     as    EmployeeInfo_ExtendedInfo ,
					a.ExtendedInfo1    as    EmployeeInfo_ExtendedInfo1 ,
					a.ExtendedInfo2    as    EmployeeInfo_ExtendedInfo2 ,

					b.UerMapInfoID   as    UerMapInfoID ,
					b.SocUserName      as    SocUserName,
					b.SocUserPassWord  as    SocUserPassWord,
					b.ExtendedInfo1   as    UerMapInfo_ExtendedInfo1,
					b.ExtendedInfo2   as    UerMapInfo_ExtendedInfo2,

					c.EmployeePurviewID as  EmployeePurviewID,
					c.PurviewInfoID     as  PurviewInfoID,
					c.ExtendedInfo   as   EmployeePurview_ExtendedInfo ,
					c.ExtendedInfo1  as   EmployeePurview_ExtendedInfo1 ,
					c.ExtendedInfo2  as   EmployeePurview_ExtendedInfo2 ,

					d.Name      as   BranchInfo_Name,
					d.Address   as   Address,
					d.Contact   as   Contact,
					d.Phone     as   BranchInfo_Phone,
					d.Content   as   Content,
					d.ExtendedInfo    as  BranchInfo_ExtendedInfo ,
					d.ExtendedInfo1   as  BranchInfo_ExtendedInfo1 ,
					d.ExtendedInfo2   as  BranchInfo_ExtendedInfo2 ,

					e.PurviewInfoID    as   PurviewInfoID ,
					e.ParentPurviewID  as   ParentPurviewID ,
					e.PurviewCode    as     PurviewCode ,
					e.Description    as     Description ,
					e.ExtendedInfo1  as     ExtendedInfo1 ,
					e.ExtendedInfo2  as     ExtendedInfo2 ,

					f.RoleInfoId   as   RoleInfoId ,
					f.Name         as   RoleInfo_Name ,
					f.RoleLevel    as   RoleLevel,
					f.ExtendedInfo   as   RoleInfo_ExtendedInfo ,
					f.ExtendedInfo1  as   RoleInfo_ExtendedInfo1 ,
					f.ExtendedInfo2  as   RoleInfo_ExtendedInfo2

	from EmployeeInfo a
					left join UerMapInfo b
					on a.EmployeeId = b.EmployeeId
					left join EmployeePurview c
					on a.EmployeeId = c.EmployeeId
					left join BranchInfo d
					on a.BranchId = d.BranchId
					left join PurviewInfo e
					on c.PurviewInfoID = e.PurviewInfoID
					left join RoleInfo f
					on a.RoleId = f.RoleInfoId
	where a.RoleId = iRoleInfoId ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getuserallinfo`
--

DROP PROCEDURE IF EXISTS `proc_getuserallinfo`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getuserallinfo`(iEmployeeId VARCHAR(60))
BEGIN
	select  a.EmployeeId 	as     EmployeeId,
					a.BranchId    as     BranchId,
					a.Name        as    EmployeeInfo_Name,
					a.`Password`    as     `Password`,
					a.CardId    	as     CardId ,
					a.RoleId    	as     RoleId ,
					a.Phone    	as     EmployeeInfo_Phone ,
					a.ExtendedInfo     as    EmployeeInfo_ExtendedInfo ,
					a.ExtendedInfo1    as    EmployeeInfo_ExtendedInfo1 ,
					a.ExtendedInfo2    as    EmployeeInfo_ExtendedInfo2 ,

					b.UerMapInfoID   as    UerMapInfoID ,
					b.SocUserName      as    SocUserName,
					b.SocUserPassWord  as    SocUserPassWord,
					b.ExtendedInfo1   as    UerMapInfo_ExtendedInfo1,
					b.ExtendedInfo2   as    UerMapInfo_ExtendedInfo2,

					c.EmployeePurviewID as  EmployeePurviewID,
					c.PurviewInfoID     as  PurviewInfoID,
					c.ExtendedInfo   as   EmployeePurview_ExtendedInfo ,
					c.ExtendedInfo1  as   EmployeePurview_ExtendedInfo1 ,
					c.ExtendedInfo2  as   EmployeePurview_ExtendedInfo2 ,

					d.Name      as   BranchInfo_Name,
					d.Address   as   Address,
					d.Contact   as   Contact,
					d.Phone     as   BranchInfo_Phone,
					d.Content   as   Content,
					d.ExtendedInfo    as  BranchInfo_ExtendedInfo ,
					d.ExtendedInfo1   as  BranchInfo_ExtendedInfo1 ,
					d.ExtendedInfo2   as  BranchInfo_ExtendedInfo2 ,

					e.PurviewInfoID    as   PurviewInfoID ,
					e.ParentPurviewID  as   ParentPurviewID ,
					e.PurviewCode    as     PurviewCode ,
					e.Description    as     Description ,
					e.ExtendedInfo1  as     ExtendedInfo1 ,
					e.ExtendedInfo2  as     ExtendedInfo2 ,

					f.RoleInfoId   as   RoleInfoId ,
					f.Name         as   RoleInfo_Name ,
					f.RoleLevel    as   RoleLevel,
					f.ExtendedInfo   as   RoleInfo_ExtendedInfo ,
					f.ExtendedInfo1  as   RoleInfo_ExtendedInfo1 ,
					f.ExtendedInfo2  as   RoleInfo_ExtendedInfo2

	from EmployeeInfo a 
					left join UerMapInfo b
					on a.EmployeeId = b.EmployeeId
					left join EmployeePurview c
					on a.EmployeeId = c.EmployeeId
					left join BranchInfo d
					on a.BranchId = d.BranchId
					left join PurviewInfo e
					on c.PurviewInfoID = e.PurviewInfoID
					left join RoleInfo f
					on a.RoleId = f.RoleInfoId
	where a.EmployeeId = iEmployeeId ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_getuserbyname_password`
--

DROP PROCEDURE IF EXISTS `proc_getuserbyname_password`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_getuserbyname_password`(iName	VARCHAR(60)
 	, iPassword		VARCHAR(60))
BEGIN
select  a.EmployeeId 	as     EmployeeId,
					a.BranchId    as     BranchId,
					a.Name        as    EmployeeInfo_Name,
					a.`Password`    as     `Password`,
					a.CardId    	as     CardId ,
					a.RoleId    	as     RoleId ,
					a.Phone    		as     EmployeeInfo_Phone ,
					a.ExtendedInfo     as    EmployeeInfo_ExtendedInfo ,
					a.ExtendedInfo1    as    EmployeeInfo_ExtendedInfo1 ,
					a.ExtendedInfo2    as    EmployeeInfo_ExtendedInfo2 ,

					b.UerMapInfoID   as    UerMapInfoID ,
					b.SocUserName      as    SocUserName,
					b.SocUserPassWord  as    SocUserPassWord,
					b.ExtendedInfo1   as    UerMapInfo_ExtendedInfo1,
					b.ExtendedInfo2   as    UerMapInfo_ExtendedInfo2,

					c.EmployeePurviewID as  EmployeePurviewID,
					c.PurviewInfoID     as  PurviewInfoID,
					c.ExtendedInfo   as   EmployeePurview_ExtendedInfo ,
					c.ExtendedInfo1  as   EmployeePurview_ExtendedInfo1 ,
					c.ExtendedInfo2  as   EmployeePurview_ExtendedInfo2 ,

					d.Name      as   BranchInfo_Name,
					d.Address   as   Address,
					d.Contact   as   Contact,
					d.Phone     as   BranchInfo_Phone,
					d.Content   as   Content,
					d.ExtendedInfo    as  BranchInfo_ExtendedInfo ,
					d.ExtendedInfo1   as  BranchInfo_ExtendedInfo1 ,
					d.ExtendedInfo2   as  BranchInfo_ExtendedInfo2 ,

					e.PurviewInfoID    as   PurviewInfoID ,
					e.ParentPurviewID  as   ParentPurviewID ,
					e.PurviewCode    as     PurviewCode ,
					e.Description    as     Description ,
					e.ExtendedInfo1  as     ExtendedInfo1 ,
					e.ExtendedInfo2  as     ExtendedInfo2 ,

					f.RoleInfoId   as   RoleInfoId ,
					f.Name         as   RoleInfo_Name ,
					f.RoleLevel    as   RoleLevel,
					f.ExtendedInfo   as   RoleInfo_ExtendedInfo ,
					f.ExtendedInfo1  as   RoleInfo_ExtendedInfo1 ,
					f.ExtendedInfo2  as   RoleInfo_ExtendedInfo2

	from EmployeeInfo a
					left join UerMapInfo b
					on a.EmployeeId = b.EmployeeId
					left join EmployeePurview c
					on a.EmployeeId = c.EmployeeId
					left join BranchInfo d
					on a.BranchId = d.BranchId
					left join PurviewInfo e
					on c.PurviewInfoID = e.PurviewInfoID
					left join RoleInfo f
					on a.RoleId = f.RoleInfoId
	where  a.Name = iName AND a.`Password` = iPassword;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_info_deletebyid`
--

DROP PROCEDURE IF EXISTS `proc_info_deletebyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_info_deletebyid`(id VARCHAR(60)
        ,itable VARCHAR(2000))
BEGIN
        declare idcolumn varchar(2000);

        IF  itable='BranchInfo'
        THEN   SET idcolumn='BranchId';

        ELSEIF  itable='ClientInfo'
        THEN   SET idcolumn='ClientId';

        ELSEIF  itable='PurviewInfo'
        THEN   SET idcolumn='PurviewInfoID';

        ELSEIF  itable='RoleInfo'
        THEN   SET idcolumn='RoleInfoId';

        ELSEIF  itable='RoleInfoPurview'
        THEN   SET idcolumn='RoleInfoPurviewID';

        ELSEIF  itable='EmployeeInfo'
        THEN   SET idcolumn='EmployeeId';

        ELSEIF  itable='EmployeePurview'
        THEN   SET idcolumn='EmployeeID';

        ELSEIF  itable='UerMapInfo'
        THEN   SET idcolumn='UerMapInfoID';

        ELSEIF  itable='ProduceInfo'
        THEN   SET idcolumn='ProduceId';

        ELSEIF  itable='BusInessInfo'
        THEN   SET idcolumn='BusInessInfoId';

        ELSEIF  itable='BusinessRelateInfo'
        THEN   SET idcolumn='BusinessRelateInfoId';

        ELSEIF  itable='BusinessFIleInfo'
        THEN   SET idcolumn='RecordId';

        ELSEIF  itable='KeyValeInfo'
        THEN   SET idcolumn='KeyValeInfoId';
        END IF;

        set @sql= 'DELETE FROM ';
        set @sql=concat(@sql,itable,' WHERE ', idcolumn, ' = \'', id,'\'');
        prepare strsql  from @sql;
        execute strsql;
        deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_iscredenitialexist`
--

DROP PROCEDURE IF EXISTS `proc_iscredenitialexist`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_iscredenitialexist`(iCredenitial VARCHAR(60))
BEGIN
        select ClientId,
                Name,
                Credenitial,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from clientinfo
	where Credenitial=iCredenitial;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvaleinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_keyvaleinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvaleinfo_insert`(
iKeyValeInfoId VARCHAR(60)
,iType VARCHAR(60)
,iCode VARCHAR(60)
,iValue VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)

)
BEGIN

	insert into keyvaleinfo(KeyValeInfoId
				,`Type`
				,Code
				,`Value`
				,ExtendedInfo
				,ExtendedInfo1 
				,ExtendedInfo2)

	values(iKeyValeInfoId
			,iType
			,iCode
			,iValue
			,iExtendedInfo
			,iExtendedInfo1 
			,iExtendedInfo2);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvaleinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_keyvaleinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvaleinfo_select`()
BEGIN
        select KeyValeInfoId,
                `Type`,
                Code,
                `Value`,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from keyvaleinfo; 
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvaleinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_keyvaleinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvaleinfo_selectbyid`(
iKeyValeInfoId VARCHAR(60)
)
BEGIN
        select KeyValeInfoId,
                `Type`,
                Code,
                `Value`,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from keyvaleinfo
        where KeyValeInfoId=iKeyValeInfoId;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvaleinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_keyvaleinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvaleinfo_update`(iKeyValeInfoId VARCHAR(60)
,iType VARCHAR(60)
,iCode VARCHAR(60)
,iValue VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN
	update keyvaleinfo set `Type`=iType
				,Code=iCode
				,`Value`=iValue
				,ExtendedInfo=iExtendedInfo
				,ExtendedInfo1 =iExtendedInfo1
				,ExtendedInfo2=iExtendedInfo2
	where KeyValeInfoId=iKeyValeInfoId;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvalueinfo_delbyconditon`
--

DROP PROCEDURE IF EXISTS `proc_keyvalueinfo_delbyconditon`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvalueinfo_delbyconditon`(
iType VARCHAR(60),
iCode VARCHAR(60)
)
BEGIN
        delete from keyvaleinfo
        where `Type`=iType and Code = iCode;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvalueinfo_selbytype`
--

DROP PROCEDURE IF EXISTS `proc_keyvalueinfo_selbytype`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvalueinfo_selbytype`(
iType VARCHAR(60)
)
BEGIN
        select KeyValeInfoId,
                `Type`,
                Code,
                `Value`,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from keyvaleinfo
        where `Type`=iType;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_keyvalueinfo_selbytypeCode`
--

DROP PROCEDURE IF EXISTS `proc_keyvalueinfo_selbytypeCode`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_keyvalueinfo_selbytypeCode`(
iType VARCHAR(60),
iCode VARCHAR(60)
)
BEGIN
        select KeyValeInfoId,
                `Type`,
                Code,
                `Value`,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        from keyvaleinfo
        where `Type`=iType and Code = iCode;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_produceinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_produceinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_produceinfo_insert`(
	iProduceId VARCHAR(60),
	iName 	  VARCHAR(100),
	iProduceCode    VARCHAR(100),
	iPeriod	 INT(11),
	iRevenue	VARCHAR(60),
    	iMiniAmount     INT(11),
    	iRiskLevel      VARCHAR(11),
	iSerialNumber VARCHAR(100),
	iPublishBeginTime DATETIME,
	iPublishEndTime DATETIME,
	iProductionType VARCHAR(60),
	iApplicableCustomer VARCHAR(60),
	iRevenueType VARCHAR(60),
	iIncrementMoney VARCHAR(60),
	iCurrencyType VARCHAR(60),
	iSealsBranch VARCHAR(60),
	iRevenueInitialDay VARCHAR(60),
	iDeadline VARCHAR(60),
	iPaymentDay VARCHAR(1000),
	iTrusteeFee VARCHAR(1000),
	iCommissionCharge VARCHAR(60),
	iTrustee VARCHAR(100),
	iOverheadCharge VARCHAR(1000),
	iRevenueCalculation VARCHAR(1000),
	iContent VARCHAR(1000),
    	iMaxTime	INT(11),
    	iMimiTime       INT(11),
    	iStandardTime	 INT(11),
	iPrequestion	  LONGTEXT,
	iIsPublished INT(11),
	iIsEnabled INT(11),
    	iExtendedInfo 	INT(11),
    	iExtendedInfo1	VARCHAR(2000),
	iExtendedInfo2	VARCHAR(2000) )
BEGIN	
	if exists (select ProduceId from ProduceInfo where ProduceId = iProduceId) then	
		call proc_produceinfo_update(
	iProduceId,
	iName,
	iProduceCode,
	iPeriod,
	iRevenue,
	iMiniAmount,
	iRiskLevel,
	iSerialNumber,
	iPublishBeginTime,
	iPublishEndTime,
	iProductionType,
	iApplicableCustomer,
	iRevenueType,
	iIncrementMoney,
	iCurrencyType,
	iSealsBranch,
	iRevenueInitialDay,
	iDeadline,
	iPaymentDay,
	iTrusteeFee,
	iCommissionCharge,
	iTrustee,
	iOverheadCharge,
	iRevenueCalculation,
	iContent,
	iMaxTime,
	iMimiTime,
	iStandardTime,
	iPrequestion,
	iIsPublished,
	iIsEnabled,
	iExtendedInfo,
	iExtendedInfo1,
	iExtendedInfo2 );
	
	else

	INSERT INTO ProduceInfo (
		ProduceId,
		Name,
		ProduceCode,
		Period,
		Revenue,
		MiniAmount,
		RiskLevel,
		SerialNumber,
		PublishBeginTime,
		PublishEndTime,
		ProductionType,
		ApplicableCustomer,
		RevenueType,
		IncrementMoney,
		CurrencyType,
		SealsBranch,
		RevenueInitialDay,
		Deadline,
		PaymentDay,
		TrusteeFee,
		CommissionCharge,
		Trustee,
		OverheadCharge,
		RevenueCalculation,
		Content,
		MaxTime,
		MimiTime,
		StandardTime,
		Prequestion,
		IsPublished,
		IsEnabled,
		ExtendedInfo,
		ExtendedInfo1,
		ExtendedInfo2         
	)
	VALUES 	(
	iProduceId,
	iName,
   	iProduceCode,
    	iPeriod,
    	iRevenue,
    	iMiniAmount,
    	iRiskLevel,
	iSerialNumber,
	iPublishBeginTime,
	iPublishEndTime,
	iProductionType,
	iApplicableCustomer,
	iRevenueType,
	iIncrementMoney,
	iCurrencyType,
	iSealsBranch,
	iRevenueInitialDay,
	iDeadline,
	iPaymentDay,
	iTrusteeFee,
	iCommissionCharge,
	iTrustee,
	iOverheadCharge,
	iRevenueCalculation,
	iContent,
    	iMaxTime,
    	iMimiTime,
    	iStandardTime,
	iPrequestion,
	iIsPublished,
	iIsEnabled,
	iExtendedInfo,
	iExtendedInfo1,
	iExtendedInfo2);
	end if;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_produceinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_produceinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_produceinfo_select`()
BEGIN

	SELECT ProduceId,
           Name,
           ProduceCode,
           Period,
           Revenue,
           MiniAmount,
           RiskLevel,
           SerialNumber,
           PublishBeginTime,
           PublishEndTime,
           ProductionType,
           ApplicableCustomer,
           RevenueType,
           IncrementMoney,
           CurrencyType,
           SealsBranch,
           RevenueInitialDay,
           Deadline,
           PaymentDay,
           TrusteeFee,
           CommissionCharge,
           Trustee,
           OverheadCharge,
           RevenueCalculation,
           Content,
           MaxTime,
           MimiTime,
           StandardTime,
           Prequestion,
           IsPublished,
           IsEnabled,
           ExtendedInfo,
           ExtendedInfo1,
           ExtendedInfo2 FROM ProduceInfo;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_produceinfo_selectbyclientid`
--

DROP PROCEDURE IF EXISTS `proc_produceinfo_selectbyclientid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_produceinfo_selectbyclientid`( iClientId VARCHAR(60),employeeid VARCHAR(60),branchid VARCHAR(60))
BEGIN

	SELECT distinct ProduceInfo.ProduceId,
                       ProduceInfo.Name,
                       ProduceInfo.ProduceCode,
                       ProduceInfo.Period,
                       ProduceInfo.Revenue,
                       ProduceInfo.MiniAmount,
                       ProduceInfo.RiskLevel,
                       ProduceInfo.MaxTime,
                       ProduceInfo.MimiTime,
                       ProduceInfo.StandardTime,
                       ProduceInfo.Prequestion,
                       ProduceInfo.ExtendedInfo,
                       ProduceInfo.ExtendedInfo1,
                       ProduceInfo.ExtendedInfo2 
	FROM ProduceInfo,businessinfo 
	WHERE ProduceInfo.ProduceId = businessinfo.ProduceId and (businessinfo.ClientId=iClientId||iClientId="") and (businessinfo.EmployeeId=employeeid||employeeid="")and (businessinfo.BranchId=branchid||branchid="");

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_produceinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_produceinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_produceinfo_selectbyid`( iProduceId VARCHAR(60)

	 )
BEGIN

	SELECT ProduceId,
           Name,
           ProduceCode,
           Period,
           Revenue,
           MiniAmount,
           RiskLevel,
           SerialNumber,
           PublishBeginTime,
           PublishEndTime,
           ProductionType,
           ApplicableCustomer,
           RevenueType,
           IncrementMoney,
           CurrencyType,
           SealsBranch,
           RevenueInitialDay,
           Deadline,
           PaymentDay,
           TrusteeFee,
           CommissionCharge,
           Trustee,
           OverheadCharge,
           RevenueCalculation,
           Content,
           MaxTime,
           MimiTime,
           StandardTime,
           Prequestion,
           IsPublished,
           IsEnabled,
           ExtendedInfo,
           ExtendedInfo1,
           ExtendedInfo2 FROM ProduceInfo WHERE ProduceId = iProduceId ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_produceinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_produceinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_produceinfo_update`( iProduceId VARCHAR(60)
    ,iName           VARCHAR(100),
    iProduceCode    VARCHAR(100),
    iPeriod	 INT(11),
    iRevenue	VARCHAR(60),
    iMiniAmount     INT(11),
    iRiskLevel      VARCHAR(11),
	iSerialNumber VARCHAR(100),
	iPublishBeginTime DATETIME,
	iPublishEndTime DATETIME,
	iProductionType VARCHAR(60),
	iApplicableCustomer VARCHAR(60),
	iRevenueType VARCHAR(60),
	iIncrementMoney VARCHAR(60),
	iCurrencyType VARCHAR(60),
	iSealsBranch VARCHAR(60),
	iRevenueInitialDay VARCHAR(60),
	iDeadline VARCHAR(60),
	iPaymentDay VARCHAR(1000),
	iTrusteeFee VARCHAR(1000),
	iCommissionCharge VARCHAR(60),
	iTrustee VARCHAR(100),
	iOverheadCharge VARCHAR(1000),
	iRevenueCalculation VARCHAR(1000),
	iContent VARCHAR(1000),
    iMaxTime	INT(11),
    iMimiTime       INT(11),
    iStandardTime	 INT(11),
	iPrequestion	  LONGTEXT,
	iIsPublished INT(11),
	iIsEnabled INT(11),
    iExtendedInfo 	INT(11),
    iExtendedInfo1	VARCHAR(2000),
	iExtendedInfo2	VARCHAR(2000) )
BEGIN

	UPDATE ProduceInfo SET Name = iName
	, ProduceCode = iProduceCode
	, Period = iPeriod
	, Revenue = iRevenue
	, MiniAmount = iMiniAmount
	, RiskLevel = iRiskLevel,
                SerialNumber=iSerialNumber,
		PublishBeginTime=iPublishBeginTime,
		PublishEndTime=iPublishEndTime,
		ProductionType=iProductionType,
		ApplicableCustomer=iApplicableCustomer,
		RevenueType=iRevenueType,
		IncrementMoney=iIncrementMoney,
		CurrencyType=iCurrencyType,
		SealsBranch=iSealsBranch,
		RevenueInitialDay=iRevenueInitialDay,
		Deadline=iDeadline,
		PaymentDay=iPaymentDay,
		TrusteeFee=iTrusteeFee,
		CommissionCharge=iCommissionCharge,
		Trustee=iTrustee,
		OverheadCharge=iOverheadCharge,
		RevenueCalculation=iRevenueCalculation,
		Content=iContent

	, MaxTime = iMaxTime
	, MimiTime = iMimiTime
	, StandardTime = iStandardTime
	, Prequestion = iPrequestion,
                IsPublished=iIsPublished,
		IsEnabled=iIsEnabled

	, ExtendedInfo = iExtendedInfo
	, ExtendedInfo1 = iExtendedInfo1
	, ExtendedInfo2 = iExtendedInfo2
	WHERE ProduceId = iProduceId;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_purviewinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_purviewinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_purviewinfo_insert`(
iPurviewInfoID VARCHAR(60)
,iParentPurviewID VARCHAR(60)
,iPurviewCode VARCHAR(60)
,iDescription VARCHAR(128)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
)
BEGIN

	insert into purviewinfo(PurviewInfoID
				,ParentPurviewID 
				,PurviewCode 
				,Description 
				,ExtendedInfo1
				,ExtendedInfo2 )

	values(iPurviewInfoID
		,iParentPurviewID 
		,iPurviewCode 
		,iDescription 
		,iExtendedInfo1
		,iExtendedInfo2 );
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_purviewinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_purviewinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_purviewinfo_select`()
BEGIN

	select  PurviewInfoID,
                ParentPurviewID,
                PurviewCode,
                Description,
                ExtendedInfo1,
                ExtendedInfo2
	from purviewinfo;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_purviewinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_purviewinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_purviewinfo_selectbyid`(
iPurviewInfoID VARCHAR(60)
)
BEGIN

	select  PurviewInfoID,
                ParentPurviewID,
                PurviewCode,
                Description,
                ExtendedInfo1,
                ExtendedInfo2
	from purviewinfo

	where PurviewInfoID=iPurviewInfoID;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_purviewinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_purviewinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_purviewinfo_update`(iPurviewInfoID VARCHAR(60)
,iParentPurviewID VARCHAR(60)
,iPurviewCode VARCHAR(60)
,iDescription VARCHAR(128)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN

	update purviewinfo set ParentPurviewID =iParentPurviewID
			 ,PurviewCode =iPurviewCode
			 ,Description =iDescription
			 ,ExtendedInfo1=iExtendedInfo1
                         ,ExtendedInfo2=iExtendedInfo2
	where PurviewInfoID=iPurviewInfoID ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfopurview_insert`
--

DROP PROCEDURE IF EXISTS `proc_roleinfopurview_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfopurview_insert`(
iRoleInfoPurviewID VARCHAR(60)
,iRoleId VARCHAR(60)
,iPurviewInfoID VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000) )
BEGIN

	insert into roleinfopurview(RoleInfoPurviewID
			,RoleId
			,PurviewInfoID
			,ExtendedInfo
			,ExtendedInfo1
			,ExtendedInfo2)
	values(iRoleInfoPurviewID
			,iRoleId                                      			
			,iPurviewInfoID
			,iExtendedInfo
			,iExtendedInfo1
			,iExtendedInfo2);
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfopurview_select`
--

DROP PROCEDURE IF EXISTS `proc_roleinfopurview_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfopurview_select`()
BEGIN

	select RoleInfoPurviewID,
                RoleId,
                PurviewInfoID,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from roleinfopurview;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfopurview_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_roleinfopurview_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfopurview_selectbyid`(
iRoleInfoPurviewID VARCHAR(60) 
)
BEGIN

	select RoleInfoPurviewID,
                RoleId,
                PurviewInfoID,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
	from roleinfopurview 
	where RoleInfoPurviewID=iRoleInfoPurviewID;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfopurview_update`
--

DROP PROCEDURE IF EXISTS `proc_roleinfopurview_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfopurview_update`(iRoleInfoPurviewID VARCHAR(60)
,iRoleId VARCHAR(60)
,iPurviewInfoID VARCHAR(60)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000))
BEGIN

        update roleinfopurview
	set RoleId=iRoleId
            ,PurviewInfoID=iPurviewInfoID
            ,ExtendedInfo=iExtendedInfo
            ,ExtendedInfo1=iExtendedInfo1
            ,ExtendedInfo2=iExtendedInfo2
	where RoleInfoPurviewID=iRoleInfoPurviewID;   

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_roleinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfo_insert`( iRoleInfoId VARCHAR(60)
	, iName		VARCHAR(60)
	, iRoleLevel	   INT
	, iExtendedInfo 	INT(11)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000)
  , iBranchId VARCHAR(60))
BEGIN

	INSERT INTO RoleInfo (RoleInfoId,Name,RoleLevel,ExtendedInfo,ExtendedInfo1,ExtendedInfo2,BranchId)
        VALUES 	(iRoleInfoId,iName,iRoleLevel,iExtendedInfo,iExtendedInfo1,iExtendedInfo2,iBranchId);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_roleinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfo_select`()
BEGIN

	SELECT RoleInfoId,
          Name,
          RoleLevel,
          ExtendedInfo,
          ExtendedInfo1,
          ExtendedInfo2,
          BranchId FROM RoleInfo;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_roleinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfo_selectbyid`( iRoleInfoId VARCHAR(60)
	 )
BEGIN

	SELECT RoleInfoId,
          Name,
          RoleLevel,
          ExtendedInfo,
          ExtendedInfo1,
          ExtendedInfo2,
          BranchId FROM RoleInfo WHERE RoleInfoId = iRoleInfoId ;  
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_roleinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_roleinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_roleinfo_update`( iRoleInfoId VARCHAR(60)
	, iName		 VARCHAR(60)
	, iRoleLevel	    INT
	, iExtendedInfo 	INT(11)          	
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000)
  , iBranchId VARCHAR(60))
BEGIN

	UPDATE RoleInfo SET Name = iName 
	, RoleLevel = iRoleLevel
	, ExtendedInfo = iExtendedInfo 
	, ExtendedInfo1 = iExtendedInfo1 
	, ExtendedInfo2 = iExtendedInfo2
  , BranchId = iBranchId
	WHERE RoleInfoId = iRoleInfoId ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_setuserpurviewsuitrolepurview`
--

DROP PROCEDURE IF EXISTS `proc_setuserpurviewsuitrolepurview`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_setuserpurviewsuitrolepurview`(iRoleId varchar(60))
BEGIN

        delete
        from EmployeePurview
        where EmployeeId  in(select EmployeeId from EmployeeInfo where RoleId = iRoleId)
        and PurviewInfoID not in(select PurviewInfoID from RoleInfoPurview where RoleId =iRoleId);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_syncomplete`
--

DROP PROCEDURE IF EXISTS `proc_syncomplete`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_syncomplete`( id VARCHAR(60)
        ,itable VARCHAR(2000))
BEGIN
        declare idcolumn varchar(2000);

        IF  itable='BranchInfo'
        THEN   SET idcolumn='BranchId';

        ELSEIF  itable='ClientInfo'
        THEN   SET idcolumn='ClientId';

        ELSEIF  itable='PurviewInfo'
        THEN   SET idcolumn='PurviewInfoID';

        ELSEIF  itable='RoleInfo'
        THEN   SET idcolumn='RoleInfoId';

        ELSEIF  itable='RoleInfoPurview'
        THEN   SET idcolumn='RoleInfoPurviewID';

        ELSEIF  itable='EmployeeInfo'
        THEN   SET idcolumn='EmployeeId';

        ELSEIF  itable='EmployeePurview'
        THEN   SET idcolumn='EmployeeID';

        ELSEIF  itable='UerMapInfo'
        THEN   SET idcolumn='UerMapInfoID';

        ELSEIF  itable='ProduceInfo'
        THEN   SET idcolumn='ProduceId';

        ELSEIF  itable='BusInessInfo'
        THEN   SET idcolumn='BusInessInfoId';

        ELSEIF  itable='BusinessRelateInfo'
        THEN   SET idcolumn='BusinessRelateInfoId';

        ELSEIF  itable='BusinessFIleInfo'
        THEN   SET idcolumn='RecordId';

        ELSEIF  itable='KeyValeInfo'
        THEN   SET idcolumn='KeyValeInfoId';
        END IF;

        set @sql= 'UPDATE ';
        set @sql=concat(@sql,itable,' SET SyncVersion = CURRENT_TIMESTAMP  WHERE ', idcolumn, ' = \'', id,'\'');
        prepare strsql  from @sql;
        execute strsql;
        deallocate prepare strsql;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_syngetdiffrowsintable`
--

DROP PROCEDURE IF EXISTS `proc_syngetdiffrowsintable`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_syngetdiffrowsintable`(itable varchar(2000)
        ,iall int)
BEGIN
        Set  @sql= 'select * from ';
        if iall > 0
        then    set  @sql=concat(@sql, itable );
        else    set  @sql=concat(@sql, itable, ' where RowVersion!=SyncVersion');
        end if;
        PREPARE strResult FROM @SQL;
        EXECUTE strResult;
        DEALLOCATE PREPARE strResult;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_test1`
--

DROP PROCEDURE IF EXISTS `proc_test1`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_test1`(iBranchId VARCHAR(60)
,iName VARCHAR(60)
,iAddress VARCHAR(60)
,iContact VARCHAR(60)
,iPhone VARCHAR(20)
,iContent VARCHAR(20)
,iExtendedInfo INT(11)
,iExtendedInfo1 VARCHAR(2000)
,iExtendedInfo2 VARCHAR(2000)
)
BEGIN
  set @sqlCount = 'select count(branchid) from branchinfo where
  branchid = iBranchid;';
  if @sqlCount = 0
  then
        update branchinfo
        set Name=iName
          ,Address=iAddress
          ,Contact=iContact
          ,Phone=iPhone
          ,Content=iContent
          ,ExtendedInfo=iExtendedInfo
          ,ExtendedInfo1=iExtendedInfo1
          ,ExtendedInfo2=iExtendedInfo2
        where BranchId= iBranchId;
  elseif @sqlCount = 1
  then
        insert into branchinfo(
                BranchId,
                Name,
                Address,
                Contact,
                Phone,
                Content,
                ExtendedInfo,
                ExtendedInfo1,
                ExtendedInfo2
        )
        values(
                iBranchId,
                iName,
                iAddress,
                iPhone,
                iContent,
                iExtendedInfo,
                iExtendedInfo1,
                iExtendedInfo2
        );
  end if;
END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_uermapinfo_insert`
--

DROP PROCEDURE IF EXISTS `proc_uermapinfo_insert`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_uermapinfo_insert`( iUerMapInfoID VARCHAR(60)
	, iEmployeeId		VARCHAR(60)
	, iSocUserName		VARCHAR(60)
	, iSocUserPassWord	VARCHAR(60)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	INSERT INTO UerMapInfo (UerMapInfoID,EmployeeId,SocUserName,SocUserPassWord,ExtendedInfo1,ExtendedInfo2)
        VALUES 	 (iUerMapInfoID,iEmployeeId,iSocUserName,iSocUserPassWord,iExtendedInfo1,iExtendedInfo2);

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_uermapinfo_select`
--

DROP PROCEDURE IF EXISTS `proc_uermapinfo_select`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_uermapinfo_select`()
BEGIN

	SELECT  UerMapInfoID,
                EmployeeId,
                SocUserName,
                SocUserPassWord,
                ExtendedInfo1,
                ExtendedInfo2
        FROM UerMapInfo;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_uermapinfo_selectbyid`
--

DROP PROCEDURE IF EXISTS `proc_uermapinfo_selectbyid`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_uermapinfo_selectbyid`( iUerMapInfoID VARCHAR(60)
	 )
BEGIN

	SELECT  UerMapInfoID,
                EmployeeId,
                SocUserName,
                SocUserPassWord,
                ExtendedInfo1,
                ExtendedInfo2
        FROM UerMapInfo WHERE UerMapInfoID = iUerMapInfoID ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;

--
-- Definition of procedure `proc_uermapinfo_update`
--

DROP PROCEDURE IF EXISTS `proc_uermapinfo_update`;

DELIMITER $$

/*!50003 SET @TEMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ $$
CREATE DEFINER=`root`@`%` PROCEDURE `proc_uermapinfo_update`( iUerMapInfoID VARCHAR(60)
	, iEmployeeId		VARCHAR(60)
	, iSocUserName		VARCHAR(60)
	, iSocUserPassWord	VARCHAR(60)
	, iExtendedInfo1	VARCHAR(2000)
	, iExtendedInfo2	VARCHAR(2000) )
BEGIN

	UPDATE UerMapInfo SET EmployeeId = iEmployeeId
	, SocUserName = iSocUserName
	, SocUserPassWord = iSocUserPassWord
	, ExtendedInfo1 = iExtendedInfo1
	, ExtendedInfo2 = iExtendedInfo2
	WHERE UerMapInfoID = iUerMapInfoID ;

END $$
/*!50003 SET SESSION SQL_MODE=@TEMP_SQL_MODE */  $$

DELIMITER ;



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
