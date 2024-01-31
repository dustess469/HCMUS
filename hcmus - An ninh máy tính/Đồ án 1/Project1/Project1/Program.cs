using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Project1
{
    class Program
    {
        static void Main()
        {
            // Generate a secret key
            byte[] secretKey = GenerateSecretKey();

            // Encrypt a file using AES algorithm with the secret key
            string inputFile = @"C:\Users\ADMIN\Documents\KHTN - An ninh máy tính\Project1\file_in.txt";
            string encryptedFile = @"C:\Users\ADMIN\Documents\KHTN - An ninh máy tính\Project1\file_out_en.bin";
            EncryptFile(inputFile, encryptedFile, secretKey);

            // Decrypt the encrypted file using AES algorithm with the secret key
            string decryptedFile = @"C:\Users\ADMIN\Documents\KHTN - An ninh máy tính\Project1\file_out_de.txt";
            DecryptFile(encryptedFile, decryptedFile, secretKey);

            Console.WriteLine("File encryption and decryption completed.");

            // Generate RSA key pair
            using (RSA rsa = RSA.Create())
            {
                // Generate private and public keys
                RSAParameters privateKey = rsa.ExportParameters(true);
                RSAParameters publicKey = rsa.ExportParameters(false);

                // Encrypt a string using the public key
                string originalString = "Hello mot ngay that dep nha";
                byte[] encryptedData = EncryptString(originalString, publicKey);

                // Decrypt the string using the private key
                string decryptedString = DecryptString(encryptedData, privateKey);

                Console.WriteLine("Original String: " + originalString);
                Console.WriteLine("Decrypted String: " + decryptedString);
            }

            string String_SHA = "Hello ANMT!";

            // Calculate the SHA-1 hash value
            string hashValue1 = CalculateSHA1(String_SHA);

            Console.WriteLine("Original String: " + String_SHA);
            Console.WriteLine("SHA-1 Hash Value: " + hashValue1);


            // Calculate the SHA-256 hash value
            string hashValue2 = CalculateSHA256(String_SHA);

            Console.WriteLine("Original String: " + String_SHA);
            Console.WriteLine("SHA-256 Hash Value: " + hashValue2);
        }

        static byte[] GenerateSecretKey()
        {
            using (Aes aes = Aes.Create())
            {
                aes.GenerateKey();
                return aes.Key;
            }
        }

        static void EncryptFile(string inputFile, string encryptedFile, byte[] key)
        {
            using (Aes aes = Aes.Create())
            {
                aes.Key = key;

                // Generate a random IV (Initialization Vector)
                aes.GenerateIV();

                // Write the IV to the beginning of the encrypted file
                using (FileStream encryptedFileStream = File.Create(encryptedFile))
                {
                    encryptedFileStream.Write(aes.IV, 0, aes.IV.Length);
                }

                // Encrypt the file content and append to the encrypted file
                using (FileStream inputFileStream = File.Open(inputFile, FileMode.Open))    
                using (CryptoStream cryptoStream = new CryptoStream(
                    File.Open(encryptedFile, FileMode.Append),
                    aes.CreateEncryptor(),
                    CryptoStreamMode.Write))
                {
                    inputFileStream.CopyTo(cryptoStream);
                }
            }
        }

        static void DecryptFile(string encryptedFile, string decryptedFile, byte[] key)
        {
            using (Aes aes = Aes.Create())
            {
                aes.Key = key;

                // Read the IV from the encrypted file
                byte[] iv = new byte[aes.IV.Length];
                using (FileStream encryptedFileStream = File.OpenRead(encryptedFile))
                {
                    encryptedFileStream.Read(iv, 0, iv.Length);
                }

                aes.IV = iv;

                // Decrypt the file content
                using (FileStream decryptedFileStream = File.Create(decryptedFile))
                using (CryptoStream cryptoStream = new CryptoStream(
                    File.OpenRead(encryptedFile),
                    aes.CreateDecryptor(),
                    CryptoStreamMode.Read))
                {
                    cryptoStream.CopyTo(decryptedFileStream);
                }
            }
        }

        static byte[] EncryptString(string plainText, RSAParameters publicKey)
        {
            using (RSA rsa = RSA.Create())
            {
                rsa.ImportParameters(publicKey);
                byte[] plainBytes = Encoding.UTF8.GetBytes(plainText);
                byte[] encryptedBytes = rsa.Encrypt(plainBytes, RSAEncryptionPadding.Pkcs1);
                return encryptedBytes;
            }
        }

        static string DecryptString(byte[] encryptedData, RSAParameters privateKey)
        {
            using (RSA rsa = RSA.Create())
            {
                rsa.ImportParameters(privateKey);
                byte[] decryptedBytes = rsa.Decrypt(encryptedData, RSAEncryptionPadding.Pkcs1);
                string decryptedString = Encoding.UTF8.GetString(decryptedBytes);
                return decryptedString;
            }
        }

        static string CalculateSHA1(string input)
        {
            using (SHA1 sha1 = SHA1.Create())
            {
                byte[] inputBytes = Encoding.UTF8.GetBytes(input);
                byte[] hashBytes = sha1.ComputeHash(inputBytes);
                string hashValue = BitConverter.ToString(hashBytes).Replace("-", "").ToLower();
                return hashValue;
            }
        }

        static string CalculateSHA256(string input)
        {
            using (SHA256 sha256 = SHA256.Create())
            {
                byte[] inputBytes = Encoding.UTF8.GetBytes(input);
                byte[] hashBytes = sha256.ComputeHash(inputBytes);
                string hashValue = BitConverter.ToString(hashBytes).Replace("-", "").ToLower();
                return hashValue;
            }
        }
    }
}

