using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Login
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string username = Username.Text;
            string password = Password.Text;
            string connectionString = "Data Source=LAPTOP-900GO2PK;Initial Catalog=QLSV;Integrated Security=True;";

            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                try
                {
                    connection.Open();
                    //nhan vien
                    SqlCommand command1 = new SqlCommand("SP_AUTHEN_NHANVIEN", connection);
                    command1.CommandType = System.Data.CommandType.StoredProcedure;
                    command1.Parameters.AddWithValue("@TENDN", username);
                    command1.Parameters.AddWithValue("@MATKHAU", password);
                    object o1 = command1.ExecuteScalar();
                    //sinh vien
                    SqlCommand command2 = new SqlCommand("SP_AUTHEN_SINHVIEN", connection);
                    command2.CommandType = System.Data.CommandType.StoredProcedure;
                    command2.Parameters.AddWithValue("@TENDN", username);
                    command2.Parameters.AddWithValue("@MATKHAU", password);
                    object o2 = command2.ExecuteScalar();

                    if (o1 != null || o2 != null)
                    {
                        MessageBox.Show("Sign-in successful!");
                        this.Close();
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

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}