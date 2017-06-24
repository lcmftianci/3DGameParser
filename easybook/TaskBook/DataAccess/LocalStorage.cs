using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.OleDb;
using System.IO;
using System.Data.Linq;

namespace TaskBook.DataAccess
{
    public class LocalStorage
    {

        public LocalStorage(string path)
        {
            _path= path;
        }

        private string _path;

        public string ConnectionString
        {
            get { return "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + _path; }
        }

        protected void CreateDatabase()
        {
            var input = this.GetType().Assembly.GetManifestResourceStream("TaskBook.DataAccess.EmptyDB.mdb.gz");

            if (input == null)
                throw new InvalidOperationException("Database template missing.");

            FileStream output = new FileStream(_path, FileMode.Create);
            System.IO.Compression.GZipStream gz =
                new System.IO.Compression.GZipStream(input, System.IO.Compression.CompressionMode.Decompress);

            using (output)
            using (input)
            using (gz)
            {
                byte[] buffer = new byte[1024];
                int bytes;
                while ((bytes = gz.Read(buffer, 0, buffer.Length)) > 0)
                {
                    output.Write(buffer, 0, bytes);
                }

                input.Close();
                output.Close();
            }
        }

        protected bool IsDatabaseExists()
        {
            return System.IO.File.Exists(_path);
        }

        public void EnsureDatabase()
        {
            if (!IsDatabaseExists())
                CreateDatabase();

            Test();
            //DataContext dc = new DataContext(CreateConnection());
            //StringWriter log = new StringWriter();
            //dc.Log = log;

            //UserOptionItem item = null;
            //foreach (var obj in dc.GetTable<UserOptionItem>())
            //{
            //    if (item == null) item = obj;
            //    Console.WriteLine("{0}=\"{1}\"", obj.Key, obj.ValueText);
            //}

            //item.ValueText = "xxxxxx";

            //try
            //{
            //    dc.SubmitChanges();
            //}
            //catch
            //{
            //    Console.WriteLine(log.ToString());
            //    log.Close();
            //    throw;
            //}
            //dc.Dispose();
        }

        private void Test()
        {
            using (var conn = CreateConnection())
            {
                conn.Open();

                var cmd = conn.CreateCommand();

                cmd.CommandText = "update [UserOptions] set [TextValue]='DDD' where [Key]='Opt1'";
                cmd.Parameters.AddWithValue("@value", "AAAAAA");
                cmd.Parameters.AddWithValue("@key", "Opt1");

                cmd.ExecuteNonQuery();


            }
        }

        private OleDbConnection CreateConnection()
        {
            var conn = new OleDbConnection(ConnectionString);
            return conn;
        }

        public Task[] GetTasks()
        {

            
            
            
            using (OleDbConnection conn = CreateConnection())
            {
                conn.Open();

                var cmd = conn.CreateCommand();
                cmd.CommandType = System.Data.CommandType.Text;
                cmd.CommandText = "SELECT Id, CreationTime, Contents, ContentsRtf, Category, RemindingTime, Reminded, FinishTime, Finished, Importance FROM Tasks ORDER BY CreationTime DESC";

                var reader = cmd.ExecuteReader();
                List<Task> list = new List<Task>();

                while (reader.Read())
                {
                    Task task = new Task();
                    task.BeginLoad();

                    task.Id = reader.GetGuid(0);

                    task.CreationTime = reader.GetDateTime(1);

                    if (!reader.IsDBNull(2))
                        task.Contents = reader.GetString(2);

                    if (!reader.IsDBNull(3))
                        task.ContentsRtf = reader.GetString(3);

                    if (!reader.IsDBNull(4))
                        task.Category = reader.GetString(4);

                    if (!reader.IsDBNull(5))
                        task.RemindingTime = reader.GetDateTime(5);

                    task.Reminded = reader.GetBoolean(6);

                    if (!reader.IsDBNull(7))
                        task.FinishTime = reader.GetDateTime(7);

                    task.Finished = reader.GetBoolean(8);

                    task.Importance = (TaskImportance)reader.GetInt32(9);

                    task.EndLoad();

                    list.Add(task);
                }

                reader.Close();

                return list.ToArray();
            }
        }


    }

}
