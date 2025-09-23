USE hellmo

--A
CREATE PROCEDURE sp_Print_HelloWorld
AS
	Print 'Hello World !!!'
	
--Kiểm tra
Exec sp_Print_HelloWorld


--B
CREATE PROCEDURE sp_Print_Tong_2 @So1 int, @So2 int
AS
	DECLARE @Tong int
	SET @Tong = @So1 + @So2
	Print @Tong

--Kiểm tra
Exec sp_Print_Tong_2 10, 12
Exec sp_Print_Tong_2 1, -2


--C
CREATE PROCEDURE sp_Tong_2 @So1 int, @So2 int, @Tong int out
AS
	SET @Tong = @So1 + @So2

--Kiểm tra
DECLARE @Sum int
Exec sp_Tong_2 1, -2, @Sum out
Print @Sum


--D
CREATE PROCEDURE sp_Tong_3 @So1 int, @So2 int,@So3 int
AS
	DECLARE @Tong int
	Exec sp_Tong_2 @So1, @So2, @Tong out
	SET @Tong = @Tong + @So3
	Print @Tong

--Kiểm tra
Exec sp_Tong_3 1, -2, 3


--E
CREATE PROCEDURE sp_Tong_MN @m int, @n int
AS
	DECLARE @Tong int
	DECLARE @i int
	SET @Tong = 0
	SET @i = @m
	
	WHILE (@i < @n)
	BEGIN
		SET @Tong = @Tong + @i
		SET @i = @i + 1
	END
	
	Print @Tong

--Kiểm tra
Exec sp_Tong_MN -1, 5


--F
CREATE PROCEDURE sp_checkNguyento @num int, @check bit out
AS
	DECLARE @bound float
	DECLARE @i int
	SET @check = 1
	SET @i = 2
	SET @bound = SQRT(@num)
	
	While (@i <= @bound)
	BEGIN
		IF (@num % @i = 0)
			BEGIN
				SET @check = 0
				break
			END
		SET @i = @i + 1		
	END

--Kiểm tra
DECLARE @check bit
Exec sp_checkNguyento 2, @check out
IF (@check = 1)
	BEGIN
		Print N'2 là số nguyên tố.'
	END
ELSE
	BEGIN
		Print N'2 không là số nguyên tố.'
	END
Exec sp_checkNguyento 4, @check out
IF (@check = 1)
	BEGIN
		Print N'4 là số nguyên tố.'
	END
ELSE
	BEGIN
		Print N'4 không là số nguyên tố.'
	END


--G	
CREATE PROCEDURE sp_Print_TongNguyenTo_MN @m int, @n int
AS
	DECLARE @Tong int
	DECLARE @i int
	DECLARE @check bit
	SET @Tong = 0
	SET @i = @m
	
	While (@i <= @n)
	BEGIN
		Exec sp_checkNguyento @i, @check out
		IF (@check = 1)
			BEGIN
				SET @Tong = @Tong + @i
			END
			
		SET @i = @i + 1
	END
	
	Print '[' + cast(@m AS VARCHAR(12)) + ' , ' + cast(@n AS VARCHAR(12)) + '] = ' + cast(@Tong AS VARCHAR(12))

--Kiểm tra
Exec sp_Print_TongNguyenTo_MN 1, 5


--H
CREATE PROCEDURE sp_UCLN @a int, @b int, @ret int out
AS
	SET @a = ABS(@a)
	SET @b = ABS(@b)
	
	IF (@a = 0 OR @b = 0)
		BEGIN
			SET @ret = @a + @b
		END
	ELSE
		BEGIN
			While (@a <> @b)
			BEGIN
				IF (@a > @b)
					SET @a = @a - @b
				ELSE
					SET @b = @b - @a
			END
		END
	
	SET @ret = @a

--Kiểm tra
DECLARE @UCLN int
Exec sp_UCLN 12, 20, @UCLN out
Print @UCLN


--I
CREATE PROCEDURE sp_BCNN @a int, @b int, @ret int out
AS
	DECLARE @temp int 
	
	Exec sp_UCLN @a, @b, @temp out
	
	SET @ret = ABS(@a * @b) / @temp

--Kiểm tra
DECLARE @BCNN int
Exec sp_BCNN 12, 20, @BCNN out
Print @BCNN


--J
CREATE PROCEDURE sp_Giaovien
AS
	SELECT * FROM GIAOVIEN

--Kiểm tra
Exec sp_Giaovien


--K
CREATE PROCEDURE sp_SLDetai @MaGV VARCHAR(9)
AS
	DECLARE @ret int
	SET @ret = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'Số lượng đề tài của GV ' + @MaGV + ' = ' + CAST(@ret AS VARCHAR(12))

--Kiểm tra
Exec sp_SLDetai '001'


--L
CREATE PROCEDURE sp_Print_Giaovien @MaGV VARCHAR(9)
AS
	DECLARE @HoTen NVARCHAR(30)
	SET @HoTen = (SELECT HOTEN FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Họ tên: ' + @HoTen
	
	DECLARE @Luong decimal(18,1)
	SET @Luong = (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Lương: ' + CAST(@Luong AS VARCHAR(12))
	
	DECLARE @NGSINH date
	SET @NGSINH = (SELECT NGSINH FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Ngày sinh: ' + CAST(@NGSINH AS VARCHAR(12))
	
	DECLARE @DiaChi nvarchar(50)
	Set @DiaChi = (SELECT DIACHI FROM GIAOVIEN WHERE MAGV = @MaGV)
	Print N'Địa chỉ: ' + @DiaChi
	
	DECLARE @SLDT int
	SET @SLDT = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'Số lượng đề tài: ' + CAST(@SLDT AS VARCHAR(12))
	
	DECLARE @SLNT int
	SET @SLNT = (SELECT COUNT(*) FROM NGUOI_THAN WHERE MAGV = @MaGV GROUP BY MAGV)
	Print N'Số lượng nhân thân: ' + CAST(@SLNT AS VARCHAR(12))

--Kiểm tra
Exec sp_Print_Giaovien '001'


--M
CREATE PROCEDURE sp_Check_exist_Giaovien @MaGV varchar(9), @check bit out
AS
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @MaGV))
		BEGIN
			Print @MaGV + N' tồn tại giáo viên.'
			SET @check = 1
		END
	ELSE
		BEGIN
			Print @MaGV + N' không tồn tại giáo viên.'
			SET @check = 0
		END
		
--Kiểm tra
DECLARE @check bit
Exec sp_Check_exist_Giaovien '001', @check out
Exec sp_Check_exist_Giaovien '100', @check out


--N
CREATE PROCEDURE sp_Check_regulation_Giaovien @MaGV VARCHAR(9), @MaDT VARCHAR(3), @check bit out
AS
	DECLARE @GVCNDT VARCHAR(3)
	SET @GVCNDT = (SELECT GVCNDT FROM DETAI WHERE MADT = @MaDT)
	
	IF ((SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGV) = (SELECT MABM FROM GIAOVIEN WHERE MAGV = @GVCNDT))
		BEGIN
			Print 'TRUE'
			Set @check = 1
		END
	ELSE
		BEGIN
			Print 'FALSE'
			Set @check = 0
		END

--Kiểm tra
DECLARE @check bit
Exec sp_Check_regulation_Giaovien '002', '003', @check out


--P
CREATE PROCEDURE sp_Delete_Giaovien @MaGV VARCHAR(9)
AS
	DECLARE @check bit
	SET @check = 1
	
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE MAGV = @MaGV))
		BEGIN
			IF (EXISTS(SELECT * FROM NGUOI_THAN WHERE MAGV = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên tồn tại người thân!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM THAMGIADT WHERE MAGV = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên có tham gia đề tại!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên đang là trưởng bộ môn!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM KHOA WHERE TRUONGKHOA = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên đang là trưởng khoa!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM DETAI WHERE GVCNDT = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên đang chủ nhiệm đề tài!'
					SET @check = 0
				END
				
			IF (EXISTS(SELECT * FROM GV_DT WHERE MAGV = @MaGV))
				BEGIN
					Print N'Lỗi: Giáo viên có tồn tại số điện thoại!'
					SET @check = 0
				END
				
			IF (@check = 1)
				BEGIN
					DELETE FROM GIAOVIEN WHERE MAGV = @MaGV
					Print N'Xóa thành công.'
				END
		END
	ELSE
		Print N'Giáo viên ' +@MaGV + N' không tồn tại giáo viên!'

--Kiểm tra
Exec sp_Delete_Giaovien '001'
Exec sp_Delete_Giaovien '100'


--Q
-- using cursor
CREATE PROCEDURE sp_GiaoVien_SLDetai
AS
	DECLARE cs_DSGV CURSOR FOR (SELECT MAGV FROM GIAOVIEN)
	OPEN cs_DSGV
	
	DECLARE @MaGV VARCHAR(3)
	FETCH NEXT FROM cs_DSGV INTO @MaGV
	
	WHILE (@@FETCH_STATUS = 0)
	BEGIN
		DECLARE @HoTen NVARCHAR(30)
		SET @HoTen = (SELECT HOTEN FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Họ tên: ' + @HoTen
		
		DECLARE @Luong DECIMAL(18,1)
		SET @Luong = (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Lương: ' + CAST(@Luong AS VARCHAR(12))
		
		DECLARE @NGSINH DATE
		SET @NGSINH = (SELECT NGSINH FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Ngày sinh: ' + CAST(@NGSINH AS VARCHAR(12))
		
		DECLARE @DiaChi NVARCHAR(50)
		Set @DiaChi = (SELECT DIACHI FROM GIAOVIEN WHERE MAGV = @MaGV)
		Print N'Địa chỉ: ' + @DiaChi
		
		DECLARE @SLDT int
		SET @SLDT = (SELECT COUNT(DISTINCT MADT) FROM THAMGIADT WHERE MAGV = @MaGV GROUP BY MAGV)
		Print N'Số lượng đề tài: ' + CAST(@SLDT AS VARCHAR(12))
		
		DECLARE @SLNT int
		SET @SLNT = (SELECT COUNT(*) FROM NGUOI_THAN WHERE MAGV = @MaGV GROUP BY MAGV)
		Print N'Số thân nhân: ' + CAST(@SLNT AS VARCHAR(12))
		
		DECLARE @SoGVQL int
		SET @SoGVQL = (SELECT COUNT(*) FROM GIAOVIEN WHERE GVQLCM = @MaGV)
		Print N'Số giáo viên mà giáo viên ' + @MaGV + N' quản lý: ' + CAST(@SoGVQL AS VARCHAR(12))
		
		FETCH NEXT FROM cs_GiaoVien INTO @MaGV  
	END
	
	CLOSE cs_GiaoVien
	DEALLOCATE cs_GiaoVien

--Kiểm tra
Exec sp_GiaoVien_SLDetai


--R
CREATE PROCEDURE sp_Check_regulation_Giaovien_ab @MaGVA VARCHAR(9), @MaGVB VARCHAR(9)
AS
	IF ((SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGVA) = (SELECT MABM FROM GIAOVIEN WHERE MAGV = @MaGVB))
		IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGVA))
			IF ((SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVA) < (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVB))
				BEGIN
					Print 'FALSE'
				END
			ELSE
				BEGIN
					Print 'TRUE'
				END
		ELSE 
			IF (EXISTS(SELECT * FROM BOMON WHERE TRUONGBM = @MaGVB))
				IF ((SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVA) > (SELECT LUONG FROM GIAOVIEN WHERE MAGV = @MaGVB))
					Print 'FALSE'
				ELSE
					Print 'TRUE'
			ELSE
				Print 'TRUE'
	ELSE
		Print 'TRUE'

--Kiểm tra
Exec sp_Check_regulation_Giaovien_ab '002', '003'


--S
CREATE PROCEDURE sp_Add_Giaovien @MaGV VARCHAR(9), @HoTen NVARCHAR(30), @Luong int, @Phai NCHAR(3), 
	@NgSinh DATE, @DiaChi NVARCHAR(100), @GVQLCM VARCHAR(3), @MaBM  NCHAR(4)
AS
	DECLARE @check bit
	SET @check = 1
	
	IF (EXISTS(SELECT * FROM GIAOVIEN WHERE HOTEN = @HoTen))
		BEGIN
			Print N'Lỗi: Trùng họ tên giáo viên khác'
			SET @check = 0
		END
		
	IF (YEAR(GetDate()) - YEAR(@NgSinh) < 18)
		BEGIN
			Print N'Lỗi: Tuổi <= 18!'
			SET @check = 0
		END
		
	IF (@Luong <= 0)
		BEGIN
			Print N'Lỗi: Lương <= 0!'
			SET @check = 0
		END
	
	IF (@check = 1)
		BEGIN
			INSERT INTO GIAOVIEN(MAGV, HOTEN, LUONG, PHAI, NGSINH, DIACHI, GVQLCM, MABM)
			VALUES (@MaGV, @HoTen, @Luong, @Phai, @NgSinh, @DiaChi, @GVQLCM, @MaBM)
			Print N'Thêm thành công!'
		END

--Kiểm tra
Exec sp_Add_Giaovien '100', N'Ngô Gia Ngân', 1500, N'Nữ', '15/01/1999', N'219 Nguyễn Văn Cừ, Phường 4, Quận 5, TP.HCM', NULL, NULL