import os

def recover_images(volume_file, output_dir):
    # Định nghĩa các đặc trưng (signature) của định dạng JPG và PNG
    JPG_HEADER = b'\xFF\xD8\xFF'
    JPG_FOOTER = b'\xFF\xD9'
    PNG_HEADER = b'\x89\x50\x4E\x47\x0D\x0A\x1A\x0A'
    PNG_FOOTER = b'\x49\x45\x4E\x44\xAE\x42\x60\x82'

    # Tạo thư mục lưu ảnh phục hồi
    os.makedirs(output_dir, exist_ok=True)

    recovered_count = 0
    with open(volume_file, 'rb') as vol:
        data = vol.read()

        # Phục hồi JPG
        index = 0
        while index < len(data):
            start = data.find(JPG_HEADER, index)
            if start == -1:
                break
            end = data.find(JPG_FOOTER, start) + len(JPG_FOOTER)
            if end == -1:
                break

            # Lưu ảnh JPG
            recovered_count += 1
            with open(f"{output_dir}/Recovered_{recovered_count:04d}.jpg", 'wb') as img_file:
                img_file.write(data[start:end])

            index = end

        # Phục hồi PNG
        index = 0
        while index < len(data):
            start = data.find(PNG_HEADER, index)
            if start == -1:
                break
            end = data.find(PNG_FOOTER, start) + len(PNG_FOOTER)
            if end == -1:
                break

            # Lưu ảnh PNG
            recovered_count += 1
            with open(f"{output_dir}/Recovered_{recovered_count:04d}.png", 'wb') as img_file:
                img_file.write(data[start:end])

            index = end

    print(f"Đã phục hồi {recovered_count} file ảnh vào thư mục '{output_dir}'.")


# Đường dẫn đến file volume và thư mục lưu file phục hồi
volume_path = 'F:/Image00.Vol'
output_directory = 'D:/RecoveredImages'

# Gọi hàm phục hồi
recover_images(volume_path, output_directory)
