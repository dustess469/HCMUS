--Tao CSDL--
GO
CREATE DATABASE QLDoiBong
GO
USE QLDoiBong


--Tao bang--
CREATE TABLE DOI
(
	IDDoi char(10),
	TenDoi nvarchar(30),
	DoiTruong char(10),
	SoLuong char(10)
	PRIMARY KEY(IDDOI)
)

CREATE TABLE BOTRI
(
	IDDOI char(10),
	IDThanhVien char(10),
	DiaChi nvarchar(30),
	NhiemVu nvarchar(50),
	QuanLi char(10)
	PRIMARY KEY (IDDOI, IDThanhVien)
)

CREATE TABLE THANHVIEN
(
	IDThanhVien char(10),
	HoTen nvarchar(30),
	SoCMND char(10),
	DiaChi nvarchar(30),
	NgaySinh datetime
	PRIMARY KEY (IDThanhVien)
)


--Khoa ngoai--
GO
ALTER TABLE BOTRI
ADD CONSTRAINT FK_BOTRI_DOI
FOREIGN KEY (IDDOI)
REFERENCES DOI(IDDOI)


ALTER TABLE BOTRI
ADD CONSTRAINT FK_BOTRI_THANHVIEN
FOREIGN KEY (IDThanhVien)
REFERENCES THANHVIEN(IDThanhVien)


--Nhap du lieu--
GO
INSERT INTO DOI VALUES ('2', N'Đội Tân Phú', '1', NULL)
INSERT INTO DOI VALUES ('7', N'Đội Bình Phú', '5', NULL)

INSERT INTO BOTRI VALUES ('2', '2', N'123 Vườn Lài Tân Phú', N'Trực khu vực vòng xoay 1', '1')
INSERT INTO BOTRI VALUES ('2', '1', N'45 Phú Thọ Hòa Tân Phú', N'Theo dõi hoạt động', '1')
INSERT INTO BOTRI VALUES ('7', '3', N'11 Chợ lớn Bình Phú', NULL, '5')
INSERT INTO BOTRI VALUES ('7', '4', N'2 Bis Nguyễn Văn Cừ Q5', NULL, '3')
INSERT INTO BOTRI VALUES ('7', '5', N'1Bis Trần Đình Xu Q1', NULL, NULL)

INSERT INTO THANHVIEN VALUES ('1', N'Nguyễn Quan Tùng', '240674018', 'TPHCM', '01/30/2000')
INSERT INTO THANHVIEN VALUES ('2', N'Lưu Phi Nam', '240674027', N'Quảng Nam', '03/12/2001')
INSERT INTO THANHVIEN VALUES ('3', N'Lê Quang Bảo', '240674063', N'Quảng Ngãi', '05/14/1999')
INSERT INTO THANHVIEN VALUES ('4', N'Hà Ngọc Thúy', '240674504', 'TPHCM', '07/26/1998')
INSERT INTO THANHVIEN VALUES ('5', N'Trương Thị Minh', '240674405', N'Hà Nội', NULL)
INSERT INTO THANHVIEN VALUES ('6', N'Ngô Thị Thủy', '240674306', NULL, '09/18/2000')