--Tao CSDL--
GO
CREATE DATABASE QLDoiBong
GO
USE QLDoiBong

-----CAU 1-----
CREATE TABLE DOI
(
	IDDoi int,
	TenDoi nvarchar(50),
	DoiTruong int,
	SoLuong int
	PRIMARY KEY(IDDOI)
)

CREATE TABLE BOTRI
(
	IDDOI int,
	IDThanhVien int,
	DiaChi nvarchar(50),
	NhiemVu nvarchar(50),
	QuanLi char(50)
	PRIMARY KEY (IDDOI, IDThanhVien)
)

CREATE TABLE THANHVIEN
(
	IDThanhVien int,
	HoTen nvarchar(50),
	SoCMND char(20),
	DiaChi nvarchar(50),
	NgaySinh date
	PRIMARY KEY (IDThanhVien)
)


-----CAU 2-----
GO
ALTER TABLE BOTRI
ADD CONSTRAINT FK_BOTRI_DOI
FOREIGN KEY (IDDOI)
REFERENCES DOI(IDDOI)


ALTER TABLE BOTRI
ADD CONSTRAINT FK_BOTRI_THANHVIEN
FOREIGN KEY (IDThanhVien)
REFERENCES THANHVIEN(IDThanhVien)


-----CAU 3-----
GO
INSERT INTO DOI VALUES ('2', N'Đội Tân Phú',  '1', NULL)
INSERT INTO DOI VALUES ('7', N'Đội Bình Phú', '5', NULL)

INSERT INTO BOTRI VALUES ('2', '2', N'123 Vườn Lài Tân Phú',   N'Trực khu vực vòng xoay 1', '1')
INSERT INTO BOTRI VALUES ('2', '1', N'45 Phú Thọ Hòa Tân Phú', N'Theo dõi hoạt động',       '1')
INSERT INTO BOTRI VALUES ('7', '3', N'11 Chợ lớn Bình Phú',    NULL,                        '5')
INSERT INTO BOTRI VALUES ('7', '4', N'2 Bis Nguyễn Văn Cừ Q5', NULL,                        '3')
INSERT INTO BOTRI VALUES ('7', '5', N'1Bis Trần Đình Xu Q1',   NULL,                        NULL)

INSERT INTO THANHVIEN VALUES ('1', N'Nguyễn Quan Tùng', '240674018', N'TPHCM',      '01/30/2000')
INSERT INTO THANHVIEN VALUES ('2', N'Lưu Phi Nam',      '240674027', N'Quảng Nam',  '03/12/2001')
INSERT INTO THANHVIEN VALUES ('3', N'Lê Quang Bảo',     '240674063', N'Quảng Ngãi', '05/14/1999')
INSERT INTO THANHVIEN VALUES ('4', N'Hà Ngọc Thúy',     '240674504', N'TPHCM',      '07/26/1998')
INSERT INTO THANHVIEN VALUES ('5', N'Trương Thị Minh',  '240674405', N'Hà Nội',     NULL)
INSERT INTO THANHVIEN VALUES ('6', N'Ngô Thị Thủy',     '240674306', NULL,          '09/18/2000')


-----CAU 4-----
SELECT DOI.TenDoi AS TenDoi, THANHVIEN.HoTen AS TenDoiTruong
FROM BOTRI
JOIN DOI ON BOTRI.IDDoi = DOI.IDDoi
JOIN THANHVIEN ON BOTRI.IDThanhVien = THANHVIEN.IDThanhVien
WHERE BOTRI.DiaChi = N'Tân Phú';


-----CAU 5-----
SELECT THANHVIEN.HoTen AS TenQuanLy,
    COUNT(DISTINCT BOTRI.IDThanhVien) AS SoLuongThanhVien, THANHVIEN.NgaySinh
FROM THANHVIEN
JOIN BOTRI ON THANHVIEN.IDThanhVien = BOTRI.QuanLi
GROUP BY THANHVIEN.HoTen, THANHVIEN.NgaySinh;