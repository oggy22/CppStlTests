using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public static class MultiDictionaryExtensions
    {
        public static MultiDictionary<Key, Value> IntersectWith<Key, Value>(this MultiDictionary<Key, Value> multiDictionary, MultiDictionary<Key, Value> other)
        {
            List<Key> keys = multiDictionary.GetKeys().ToList();
            foreach (Key key in keys)
            {
                if (!other.GetOrDefault(key).Any())
                    multiDictionary.RemoveKey(key);
            }

            foreach (Key key in multiDictionary.GetKeys())
            {
                List<Value> toRemove = multiDictionary.GetOrDefault(key).Where(value => !other.Get(key).Contains(value)).ToList();
                foreach (Value value in toRemove) { multiDictionary.Remove(key, value); }
            }

            return multiDictionary;
        }
    }
}
