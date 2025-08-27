using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public class MyHashSet<T> where T : notnull
    {
        List<T>[] array = new List<T>[11];

        private int GetIndex(T item)
        {
            return Math.Abs(item.GetHashCode()) % array.Length;
        }

        public void Add(T item)
        {
            int index = GetIndex(item);
            var list = array[index];
            if (list == null)
            {
                array[index] = [item];
                return;
            }

            if (!list.Contains(item))
            {
                list.Add(item);
            }
        }

        public bool Contains(T item)
        {
            int index = GetIndex(item);
            var list = array[index];
            if (list == null) return false;
            return list.Contains(item);
        }

        public bool Remove(T item)
        {
            int index = GetIndex(item);
            var list = array[index];
            if (list == null) return false;
            return list.Remove(item);
        }

        public int Count()
        {
            int count = 0;
            foreach (var list in array)
            {
                if (list != null)
                {
                    count += list.Count;
                }
            }
            return count;
        }
    }

    public class MyHashSetTest
    {
        [SetUp]
        public void Setup()
        {

        }

        [Test]
        public void Basic()
        {
            MyHashSet<string> set = new();

            set.Add("test1");
            set.Add("test2");
            Assert.That(set.Count(), Is.EqualTo(2));

            Assert.IsTrue(set.Contains("test1"));
            Assert.IsTrue(set.Contains("test2"));
            Assert.IsFalse(set.Contains("test3"));

            Assert.IsTrue(set.Remove("test1"));
            Assert.IsFalse(set.Contains("test1"));
            Assert.That(set.Count(), Is.EqualTo(1));
        }

        [Test]
        public void Basic2()
        {
            Dictionary<int?, int> dict = new Dictionary<int?, int>();
            dict[1] = 1;
            var d = new Dictionary<int?, string>();
        }

    }
}
