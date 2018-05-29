using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LinqTest
{

  enum GradeLevel { FirstYear = 1, SecondYear, ThirdYear, FourthYear };

  class Student
  {
    public string FirstName { get; set; }
    public string LastName { get; set; }
    public int ID { get; set; }
    public GradeLevel Year;
    public List<int> ExamScores;
  }

  class LinqTest
  {
    public delegate void Handler<T>(T data);

    public static void Print<T>(T i)
    {
      Console.Write(i + " ");
    }

    public static void OutPut<T>(IEnumerable<T> data, Handler<T> hand)
    {
      foreach (var i in data)
      {
        hand(i);
      }
    }


    public static void test1()
    {
      int[] scores = new int[] { 97, 92, 81, 60 };

      // Define the query expression.
      IEnumerable<int> scoreQuery =
          from score in scores
          where score > 80
          select score;

      // Execute the query.
      foreach (int i in scoreQuery)
      {
        Console.Write(i + " ");
      }
    }

    public static void test_start()
    {
      List<int> numbers = new List<int>() { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };

      IEnumerable<int> filteringQuery =
          from num in numbers
          where num < 3 || num > 7
          orderby num descending
          select num;

      OutPut(filteringQuery, Print);
      Console.WriteLine();

      IEnumerable<int> orderingQuery =
          from num in numbers
          where num < 3 || num > 7
          orderby num ascending
          select num;

      OutPut(orderingQuery, Print);
      Console.WriteLine();

      string[] groupingQuery = { "carrots", "cabbage", "broccoli", "beans", "barley" };
      IEnumerable<IGrouping<char, string>> queryFoodGroups =
          from item in groupingQuery
          orderby item[0] ascending
          group item by item[0];

      OutPut(queryFoodGroups, delegate(IGrouping<char, string> i)
      {
        Console.Write("key " + i.Key + " \n");
      });
      Console.WriteLine();

      var out_ = groupingQuery.Where(c => c[0] == 'c');
      OutPut(out_, Print);
      Console.WriteLine();
    }

    static List<Student> students = new List<Student>
      #region student list
    {
        new Student {FirstName = "Terry", LastName = "Adams", ID = 120, 
            Year = GradeLevel.SecondYear, 
            ExamScores = new List<int>{ 99, 82, 81, 79}},
        new Student {FirstName = "Fadi", LastName = "Adams", ID = 116, 
            Year = GradeLevel.ThirdYear,
            ExamScores = new List<int>{ 99, 86, 90, 94}},
        new Student {FirstName = "Hanying", LastName = "Feng", ID = 117, 
            Year = GradeLevel.FirstYear, 
            ExamScores = new List<int>{ 93, 92, 80, 87}},
        new Student {FirstName = "Cesar", LastName = "Garcia", ID = 114, 
            Year = GradeLevel.FourthYear,
            ExamScores = new List<int>{ 97, 89, 85, 82}},
        new Student {FirstName = "Debra", LastName = "Garcia", ID = 115, 
            Year = GradeLevel.ThirdYear, 
            ExamScores = new List<int>{ 35, 72, 91, 70}},
        new Student {FirstName = "Hugo", LastName = "Garcia", ID = 118, 
            Year = GradeLevel.SecondYear, 
            ExamScores = new List<int>{ 92, 90, 83, 78}},
        new Student {FirstName = "Sven", LastName = "Mortensen", ID = 113, 
            Year = GradeLevel.FirstYear, 
            ExamScores = new List<int>{ 88, 94, 65, 91}},
        new Student {FirstName = "Claire", LastName = "O'Donnell", ID = 112, 
            Year = GradeLevel.FourthYear, 
            ExamScores = new List<int>{ 75, 84, 91, 39}},
        new Student {FirstName = "Svetlana", LastName = "Omelchenko", ID = 111, 
            Year = GradeLevel.SecondYear, 
            ExamScores = new List<int>{ 97, 92, 81, 60}},
        new Student {FirstName = "Lance", LastName = "Tucker", ID = 119, 
            Year = GradeLevel.ThirdYear, 
            ExamScores = new List<int>{ 68, 79, 88, 92}},
        new Student {FirstName = "Michael", LastName = "Tucker", ID = 122, 
            Year = GradeLevel.FirstYear, 
            ExamScores = new List<int>{ 94, 92, 91, 91}},
        new Student {FirstName = "Eugene", LastName = "Zabokritski", ID = 121,
            Year = GradeLevel.FourthYear, 
            ExamScores = new List<int>{ 96, 85, 91, 60}}
    };
      #endregion



    public static void test_from_class()
    {
      
      var highScores =
        from student 
          in students
        where student.ExamScores[2] > 90
        orderby student.ExamScores[2] descending
        select new { Name = student.FirstName, Score = student.ExamScores[2] };
      OutPut(highScores, i =>
      {
        Console.Write(i.Name + " " + i.Score + "\n");
      });
      Console.WriteLine();

      var highScoresName =
       from student
         in students
       where student.ExamScores[2] > 90
       orderby student.ExamScores[2] descending
       select student.Year.ToString();
      OutPut(highScoresName, i =>
      {
        Console.Write(i+ "\n");
      });

      var MyhighScores =
       from student
         in students
       where student.ExamScores[2] > 90
       orderby student.ExamScores[2] descending
       select student.ToString();
      OutPut(MyhighScores, i =>
      {
        Console.Write(i + "\n");
      });

      //var StudentFirstName = 
      //  from student
      //  in students
      //  where student.ExamScores[2] > 90
      //  select ()=>{
      //    return student.FirstName;
      //  };

      var GroupResult =
        from student
        in students
        group student by student.LastName into newGroup
        orderby newGroup.Count() ascending
        select newGroup;

      Console.WriteLine("start----");
      OutPut(GroupResult, i => {
        OutPut(i, e => {
          Console.Write(e.FirstName+" ");
        });
        Console.WriteLine(" new line  ...");
      });

    }

    public static void run()
    {
      test_from_class();
    }
  }
}
