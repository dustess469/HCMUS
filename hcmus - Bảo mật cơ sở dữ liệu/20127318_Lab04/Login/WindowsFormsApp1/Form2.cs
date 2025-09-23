using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.Cryptography;
using System.IO;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        private class NhanVien {
            public string ID { get; set; }
            public string fullname { get; set; }
            public string email { get; set; }
            public byte[] salary { get; set; }
            public string username { get; set; }
            public byte[] password { get; set; }
        }
        private void fetchListBox() {
            listBox1.Items.Clear();
            SqlCommand command = new SqlCommand("SP_SEL_ENCRYPT_NHANVIEN", GlobalConnection.Connection);
            command.CommandType = CommandType.StoredProcedure;
            using (SqlDataReader reader = command.ExecuteReader()) {
                while (reader.Read()) {
                    SqlBytes sqlBytes = reader.GetSqlBytes(reader.GetOrdinal("MATKHAU"));
                    byte[] passwordBytes = sqlBytes.Value;
                    sqlBytes = reader.GetSqlBytes(reader.GetOrdinal("LUONG"));
                    byte[] salarydBytes = sqlBytes.Value;

                    listBox1.Items.Add(new NhanVien {
                        ID = reader["MANV"].ToString(),
                        fullname = reader["HOTEN"].ToString(),
                        email = reader["EMAIL"].ToString(),
                        username = reader["TENDN"].ToString(),
                        salary = salarydBytes,
                        password = passwordBytes,}
                    );
                }
                reader.Close();
            }
            listBox1.DisplayMember = "ID";
        }
        public Form2() {
            InitializeComponent();
            fetchListBox();
        }

        private string Decrypt(byte[] data ) {
            SqlCommand command = new SqlCommand("DECRYPT_AES_256", GlobalConnection.Connection);
            command.CommandType = System.Data.CommandType.StoredProcedure;
            command.Parameters.AddWithValue("@LUONG", data);
            string temp = command.ExecuteScalar().ToString();
            return temp;
        }
        private object Encrypt(string data) {
            SqlCommand command = new SqlCommand("ENCRYPT_AES_256", GlobalConnection.Connection);
            command.CommandType = System.Data.CommandType.StoredProcedure;
            command.Parameters.AddWithValue("@LUONG", int.Parse(data));
            return command.ExecuteScalar();
        }

        private void clearInput() {
            textID.Text = "";
            textEmail.Text = "";
            textFullname.Text = "";
            textPassword.Text = "";
            textSalary.Text = "";
            textUsername.Text = "";
        }


        private void button1_Click(object sender, EventArgs e) {
            clearInput();
            listBox1.SelectedIndex = -1;
        }

        private void button2_Click(object sender, EventArgs e) {
            try {
                SHA1 sha1 = SHA1.Create();
                SqlCommand command = new SqlCommand("SP_INS_ENCRYPT_NHANVIEN", GlobalConnection.Connection);
                command.CommandType = CommandType.StoredProcedure;
                command.Parameters.AddWithValue("@MANV", textID.Text);
                command.Parameters.AddWithValue("@HOTEN", textFullname.Text);
                command.Parameters.AddWithValue("@EMAIL", textEmail.Text);
                command.Parameters.AddWithValue("@LUONG", Encrypt(textSalary.Text));
                command.Parameters.AddWithValue("@TENDN", textUsername.Text);
                command.Parameters.AddWithValue("@MATKHAU", sha1.ComputeHash(Encoding.UTF8.GetBytes(textPassword.Text)));

                if (command.ExecuteNonQuery() == 0) MessageBox.Show("Insert Fail");
                else MessageBox.Show("Success");

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            clearInput();
            fetchListBox();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
            {
                NhanVien selectedItem = (NhanVien)listBox1.SelectedItem;
                textID.Text = selectedItem.ID;
                textFullname.Text = selectedItem.fullname;
                textEmail.Text = selectedItem.email;
                textSalary.Text = Decrypt(selectedItem.salary);
                textUsername.Text = selectedItem.username;
                textPassword.Text = String.Join("", selectedItem.password.Select(b => b.ToString("x2")));
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
