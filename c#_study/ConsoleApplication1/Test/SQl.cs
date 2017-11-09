using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data;

namespace LinqTest {
    public class SQl {

        public static void RowSQlServer() {
            SqlConnection conn = new SqlConnection();
            string connStr = "Data Source=; User ID=wangyuan; Password=1; Initial Catalog=yuan";
            conn.ConnectionString = connStr;
            conn.Open();
            if (conn.State == ConnectionState.Open) {
                Console.WriteLine("open ok");
                Console.WriteLine(conn.ServerVersion);
                Console.WriteLine(conn.State);
            }
            else {
                Console.WriteLine("open faild");
            }
            conn.Close();
        }

        public static void myTest() {

            string commandString = 
                @"insert into 
                yuan.dbo.student(ID,name,age,class,monitor,user_info) 
                values (10000,'wei song',22,1,1,'test from sql');
                ";

            string configStr = "Data Source=; User ID=wangyuan; Password=1; Initial Catalog=yuan";
            SqlConnection conn = new SqlConnection(configStr);
            conn.Open();
            if (conn.State != ConnectionState.Open) {
                return;
            }

            SqlCommand command = new SqlCommand();
            command.Connection = conn;
            command.CommandText = commandString;
            command.ExecuteNonQuery();

            SqlCommand read = new SqlCommand();
            read.CommandText = "select * from yuan.dbo.student;";
            read.Connection = conn;
            SqlDataReader reader = read.ExecuteReader();
            while (reader.Read()) {
                var id = reader.GetInt32(0);
                var name = reader.GetString(1);
                var age = reader.GetInt32(2);
                var class_info = reader.GetInt32(3);
                var monitor = reader.GetInt32(4);
                var user_info = reader.GetString(5);
                var createTime = reader.GetDateTime(6);
                Console.WriteLine("" + id + name + age + class_info + monitor + user_info + createTime );
            }
            conn.Close();

        }

        public static void RowSqlServer2() {
            string connectonString = "Data Source=; User ID=wangyuan; Password=1; Initial Catalog=yuan";
            string commandString = "insert into yuan.dbo.student values ('100002','wei song',22,'3','Liu','test from sql')";
            string commansString_Parameter = "insert into yuan.dbo.student values (@id,@name,22,'3','Liu','test from sql')";
            string commansString_Parameter_ext = "insert into yuan.dbo.student values (@id_ext,@name_ext,22,'3','Liu','test from sql')";
            SqlConnection sqlConnection = new SqlConnection(connectonString);
            sqlConnection.Open();
            Console.WriteLine(sqlConnection.ServerVersion);
            Console.WriteLine(sqlConnection.State);
            
            // create
            {
                //SqlCommand createCommand = new SqlCommand();
                //createCommand.Connection = sqlConnection;
                //createCommand.CommandText = "create table yuan.dbo.student()";
                //createCommand.ExecuteNonQuery();
                //Console.WriteLine(sqlConnection.State);
            }
            

            // write the sql command , use sqlcommand to insert data to the datebase.  

            SqlCommand command = new SqlCommand();
            command.Connection = sqlConnection;
            command.CommandText = commandString;
            command.ExecuteNonQuery();
            Console.WriteLine(sqlConnection.State);

            // add parameters to the sql command  
            Console.WriteLine("please input user id & user name");
            string id = Console.ReadLine();
            string name = Console.ReadLine();
            command.CommandText = commansString_Parameter;
            SqlParameter sqlParameter_id = new SqlParameter("@id", id);
            SqlParameter sqlParameter_name = new SqlParameter("@name", name);
            command.Parameters.Add(sqlParameter_id);
            command.Parameters.Add(sqlParameter_name);
            command.ExecuteNonQuery();

            // another way to add sql parameters  
            Console.WriteLine("please input user id & user name");
            id = Console.ReadLine();
            name = Console.ReadLine();
            command.CommandText = commansString_Parameter_ext;
            SqlParameter sqlParameter_id_ext = new SqlParameter("@id_ext", SqlDbType.NChar, 10);
            SqlParameter sqlParameter_name_ext = new SqlParameter("@name_ext", SqlDbType.NChar, 50);
            sqlParameter_id_ext.Value = id;
            sqlParameter_name_ext.Value = name;
            command.Parameters.Add(sqlParameter_id_ext);
            command.Parameters.Add(sqlParameter_name_ext);
            command.ExecuteNonQuery();

            // read data from database  
            string readDataFormDatabase_string = "select * from test.dbo.student";
            SqlCommand readDataCommand = new SqlCommand();
            readDataCommand.CommandText = readDataFormDatabase_string;
            readDataCommand.Connection = sqlConnection;
            SqlDataReader sqlDataReader = readDataCommand.ExecuteReader();
            Console.WriteLine("//////////////////////////////////////////////////////////////////////////////");
            Console.WriteLine("id      name     age  class mentor infor  ");

            while (sqlDataReader.Read()) {
                string user_id = sqlDataReader.GetString(0);
                string user_name = sqlDataReader.GetString(1);
                int user_age = sqlDataReader.GetInt32(2);
                string user_class = sqlDataReader.GetString(3);
                string user_mentor = sqlDataReader.GetString(4);
                string user_info = sqlDataReader.GetString(5);

                // there will be filled by blank after the name, for the name is 50 length in the database. need to process the user_name  
                Console.WriteLine(user_id + user_name + user_age + user_class + user_mentor + user_info);
            }

            sqlConnection.Close();
        }

        public static void Run() {
            myTest();
        }
    }
}
