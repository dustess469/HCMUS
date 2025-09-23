-- MSSV: 20127318
-- Họ tên: Phan Trí Tài
-- Hàng: 1
-- Cột : 5
-- Đê thi: 1
--Phòng thi: C23A


--1--
SELECT DISTINCT DT.*
FROM DETAI DT
JOIN GIAOVIEN GV ON DT.GVCNDT = GV.MAGV
JOIN GV_DT GVD ON GV.MAGV = GVD.MAGV
WHERE EXISTS (
    SELECT 1
    FROM GV_DT
    WHERE GV_DT.MAGV = DT.GVCNDT
)


--2--
SELECT GV.MAGV, GV.HOTEN
FROM GIAOVIEN GV
JOIN DETAI DT ON GV.MAGV = DT.GVCNDT
JOIN CHUDE CD ON DT.MACD = CD.MACD
WHERE CD.TENCD = N'Quản lý giáo dục'
GROUP BY GV.MAGV, GV.HOTEN
HAVING COUNT(DISTINCT DT.MADT) = (
    SELECT COUNT(*)
    FROM DETAI
    WHERE MACD = (
        SELECT MACD
        FROM CHUDE
        WHERE TENCD = N'Quản lý giáo dục'
    )
)


--3--
CREATE FUNCTION fnDem_SLCongViec_Khoa 
(
    @MAKHOA CHAR(5),
    @Thang INT,
    @Nam INT
)
RETURNS INT
AS
BEGIN
    DECLARE @SoLuongCongViec INT;

    SELECT @SoLuongCongViec = COUNT(DISTINCT CV.MADT)
    FROM CONGVIEC CV
    JOIN DETAI DT ON CV.MADT = DT.MADT
    JOIN BOMON BM ON DT.MADT = BM.MABM
    JOIN KHOA K ON BM.MAKHOA = K.MAKHOA
    WHERE K.MAKHOA = @MAKHOA
    AND (
        (YEAR(CV.NGAYBD) = @Nam AND MONTH(CV.NGAYBD) = @Thang)
        OR
        (YEAR(CV.NGAYKT) = @Nam AND MONTH(CV.NGAYKT) = @Thang)
        OR
        (YEAR(CV.NGAYBD) < @Nam AND YEAR(CV.NGAYKT) > @Nam)
    );

    RETURN @SoLuongCongViec;
END;


--4--
CREATE PROCEDURE spTK_SLCongViec_Khoa
    @MAKHOA CHAR(5),
    @Nam INT
AS
BEGIN
    IF @Nam > YEAR(GETDATE())
    BEGIN
        PRINT N'Năm không hợp lệ.';
        RETURN;
    END

    DECLARE @Thang INT = 1;
    DECLARE @TotalResults INT = 0;

    CREATE TABLE TempResults (
        Thang INT,
        SLCV INT
    );

    WHILE @Thang <= 12
    BEGIN
        DECLARE @SLCV INT = dbo.fnDem_SLCongViec_Khoa(@MAKHOA, @Thang, @Nam);
        
        IF @SLCV > 0
        BEGIN
            INSERT INTO TempResults (Thang, SLCV)
            VALUES (@Thang, @SLCV);
        END

        SET @TotalResults = @TotalResults + @SLCV;

        SET @Thang = @Thang + 1;
    END

    SELECT Thang, SLCV
    FROM TempResults;

    DROP TABLE TempResults;

    RETURN @TotalResults;
END