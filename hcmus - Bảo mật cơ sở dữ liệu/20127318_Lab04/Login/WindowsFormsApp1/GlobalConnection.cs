using System.Data.SqlClient;

public static class GlobalConnection
{
    public static SqlConnection Connection;
    public static string maNV;

    static GlobalConnection()
    {
        // Set up your connection string here
        string connectionString = "Data Source=LAPTOP-900GO2PK;Initial Catalog=QLSV;Integrated Security=True;";

        // Create a new SqlConnection object using your connection string
        Connection = new SqlConnection(connectionString);
    }
}
