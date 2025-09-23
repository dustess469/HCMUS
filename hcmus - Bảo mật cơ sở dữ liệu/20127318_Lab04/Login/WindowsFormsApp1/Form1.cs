using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.Cryptography;


namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string username = textBoxUser.Text;
            string password = textBoxPassword.Text;

            SHA1 sha1 = SHA1.Create();
            byte[] passwordBytes = Encoding.UTF8.GetBytes(password);
            byte[] hashBytes = sha1.ComputeHash(passwordBytes);

            {
                try
                {
                    GlobalConnection.Connection.Open();
                    //nhan vien
                    SqlCommand command1 = new SqlCommand("SP_AUTHEN_NHANVIEN", GlobalConnection.Connection);
                    command1.CommandType = System.Data.CommandType.StoredProcedure;
                    command1.Parameters.AddWithValue("@TENDN", username);
                    command1.Parameters.AddWithValue("@MATKHAU", hashBytes);
                    object o1 = command1.ExecuteScalar();

                    //sinh vien
                    SqlCommand command2 = new SqlCommand("SP_AUTHEN_SINHVIEN", GlobalConnection.Connection);
                    command2.CommandType = System.Data.CommandType.StoredProcedure;
                    command2.Parameters.AddWithValue("@TENDN", username);
                    command2.Parameters.AddWithValue("@MATKHAU", hashBytes);
                    object o2 = command2.ExecuteScalar();

                    /*if (o1 != null)*/
                    if (o1 != null || o2 != null)
                    {
                        MessageBox.Show("Login success!");
                        if (o1 != null)
                        {
                            GlobalConnection.maNV = o1.ToString();
                            Form2 form2 = new Form2();
                            form2.Show();
                            this.Hide();
                        }

                    }
                    else
                    {
                        MessageBox.Show("Invalid username or password.");
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Sign-in failed: " + ex.Message);
                }
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
