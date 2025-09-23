/*----------------------------------------------------------
MASV:		20127318	
HO TEN:		Phan Trí Tài
LAB:		05
NGAY:		27/04/2022
----------------------------------------------------------*/
--Server A
-- Tao master key Server A
USE master
Go
CREATE MASTER KEY ENCRYPTION BY PASSWORD = '20127318'
GO
-- Mo master key vua tao de su dung
OPEN MASTER KEY DECRYPTION BY PASSWORD='20127318' 
GO
--Tao certificate QLBongDaCert
Create CERTIFICATE QLBongDaCert
With Subject = 'QLBongDaCert'

--Tao key aa hoa DB QLBongDa bang certificate vua tao bang thuat toan AES_128
USE QLBongDa
GO
CREATE DATABASE ENCRYPTION KEY
	WITH ALGORITHM = AES_128
	ENCRYPTION BY SERVER CERTIFICATE QLBongDaCert


ALTER DATABASE QLBongDa SET ENCRYPTION ON