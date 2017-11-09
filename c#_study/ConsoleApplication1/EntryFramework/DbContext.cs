using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace LinqTest.EntryFramework {

    public class ModeBase {
        public ModeBase() {
            CreateTime = DateTime.Now;
        }

        public virtual int ID { get; set; }
        public virtual DateTime CreateTime { get; set; }
    }

    public class Attr : Attribute { };

    [Attr]
    [Table("student")]
    public class student : ModeBase {
        //[Column("ID")]
        public override int ID { get; set; }
        public string name{set;get;}
        public int age{set;get;}
        public int monitor { set; get; }
        public string user_info{set;get;}
    }

    public class DbContextBase : DbContext  {
        public DbContextBase(string conn) {
            this.Database.Connection.ConnectionString = conn;
            this.Configuration.LazyLoadingEnabled = false;
            this.Configuration.ProxyCreationEnabled = false;
        }

        public void insert<T>(T value) where T : ModeBase {
            this.Set<T>().Add(value);
            this.SaveChanges();
        }

        public void update<T>(T value) where T : ModeBase {
            this.Set<T>().Attach(value);
            this.Entry<T>(value).State = EntityState.Modified;
            this.SaveChanges();
        }

        public void delete<T>(T value) where T : ModeBase {
            this.Entry<T>(value).State = EntityState.Deleted;
            this.SaveChanges();
        }

        public T find<T>(params object[] key) where T : ModeBase {
            return this.Set<T>().Find(key);
        }

        public T findById<T>(int id )where T:ModeBase{
            return this.Set<T>().SingleOrDefault(e => e.ID == id);
        }

        public List<T> findAll<T>() where T:ModeBase {
            return this.Set<T>().ToList();;
        }

        public DbSet<student> students { get; set; }
    }

    public class DbContectTest {
        public static void Test() {
            string dbconfig = @"
                Data Source=; 
                User ID=wangyuan; 
                Password=1; 
                Initial Catalog=yuan";
            using(var db = new DbContextBase(dbconfig)){
                //student stu = new student {
                //    name = "wangyuan",
                //    age = 22,
                //    monitor = 3,
                //    user_info = "这是一个个人实验"
                //};
                //for (int i = 0; i < 1000; i++){
                //    db.insert(stu);
                //}

                var result = (from s in db.students
                             where s.ID == 1000
                             select s.name).ToList();

                //var result = (from s in db.students
                //              where s.ID == 1000
                //              select s.name).ToList<string>();

                for (var i = 0; i != result.Count; i++) {
                    Console.WriteLine(result[i]);
                }
                
            }
            Console.Write("ok");

            var type = typeof(int);
        }
    }
}
