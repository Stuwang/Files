using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LinqTest {
  class Person {
    public string FirstName { get; set; }
    public string LastName { get; set; }
  }

  class Pet {
    public string Name { get; set; }
    public Person Owner { get; set; }
  }

  public delegate int Del(int a, int b);

  class Join {

    public static void NullTest() {
      int? a = 1;
      if (a.HasValue) {
        Console.WriteLine(a);
      }
      else {
        Console.WriteLine("undefined");
      }
      
    }

    public static void test() {
      Person magnus = new Person { FirstName = "Magnus", LastName = "Hedlund" };
      Person terry = new Person { FirstName = "Terry", LastName = "Adams" };
      Person charlotte = new Person { FirstName = "Charlotte", LastName = "Weiss" };
      Person arlene = new Person { FirstName = "Arlene", LastName = "Huff" };
      Person rui = new Person { FirstName = "Rui", LastName = "Raposo" };

      Pet barley = new Pet { Name = "Barley", Owner = terry };
      Pet boots = new Pet { Name = "Boots", Owner = terry };
      Pet whiskers = new Pet { Name = "Whiskers", Owner = charlotte };
      Pet bluemoon = new Pet { Name = "Blue Moon", Owner = rui };
      Pet daisy = new Pet { Name = "Daisy", Owner = magnus };

      // Create two lists.
      List<Person> people = new List<Person> { magnus, terry, charlotte, arlene, rui };
      List<Pet> pets = new List<Pet> { barley, boots, whiskers, bluemoon, daisy };

      var query =
        from p in people
        join pet in pets
          on p equals pet.Owner
        select new { OwerName = p.FirstName, PetName = pet.Name };

      LinqTest.OutPut(query, i => {
        Console.WriteLine(i.OwerName + " " + i.PetName);
      });
      Console.WriteLine("start delegete lamba...");

      Del del = (int a, int b) => {
        return a * a + b * b;
      };
      Console.WriteLine(del(1, 2));
    }
  }
}
