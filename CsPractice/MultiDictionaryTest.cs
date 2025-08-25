using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public class MultiDictionaryTest
    {
        [SetUp]
        public void Setup()
        {

        }

        [Test]
        public void Basic()
        {
            MultiDictionary<string, string> dict = new();
            dict.Add("animal", "horse");
            dict.Add("animal", "cat");
            dict.Add("animal", "dog");
            Assert.That(dict.GetOrDefault("animal").Count(), Is.EqualTo(3));
            Assert.That(dict.GetOrDefault("plant").Count(), Is.EqualTo(0));
        }

        [Test]
        public void IntersectWith()
        {
            MultiDictionary<string, string> dict = new();
            dict.Add("animal", "horse");
            dict.Add("animal", "cat");
            dict.Add("animal", "dog");
            dict.Add("plant", "palm");
            Assert.That(dict.Count(), Is.EqualTo(4));
            dict.IntersectWith(dict);
            Assert.That(dict.Count(), Is.EqualTo(4));
        }
    }
}
