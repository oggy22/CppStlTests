using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public class MultiDictionary<Key, Value>
    {
        private Dictionary<Key, HashSet<Value>> dict;

        public MultiDictionary()
        {
            dict = new();
        }

        public int Count()
        {
            return dict.Sum(pair => pair.Value.Count);
        }

        public void Add(Key key, Value val)
        {
            if (dict.TryGetValue(key, out HashSet<Value> result))
            {
                result.Add(val);
            }
            else
            {
                dict[key] = new HashSet<Value> { val };
            }
        }

        public bool Remove(Key key, Value val)
        {
            if (dict.TryGetValue(key, out HashSet<Value> result))
            {
                if (!result.Remove(val)) return false;
                result.Remove(val);
                if (result.Count == 0) dict.Remove(key);
                return true;
            }
            else
            {
                return false;
            }

        }

        public bool RemoveKey(Key key)
        {
            return dict.Remove(key);
        }

        public IEnumerable<Value> GetOrDefault(Key key)
        {
            if (dict.TryGetValue(key, out HashSet<Value> result))
            {
                foreach (Value val in result) yield return val;
            }
            else
            {
                yield break;
            }
        }


        public IEnumerable<Key> GetKeys()
        {
            foreach (Key key in dict.Keys)
            {
                yield return key;
            }
        }

        public IEnumerable<Value> Get(Key key)
        {
            if (dict.TryGetValue(key, out HashSet<Value> result))
            {
                foreach (Value val in result) yield return val;
            }
            else
            {
                throw new KeyNotFoundException($"The key {key} not found");
            }
        }
    }
}
