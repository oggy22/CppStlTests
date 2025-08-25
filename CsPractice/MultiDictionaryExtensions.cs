using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsPractice
{
    public static class MultiDictionaryExtensions
    {
        public static MultiDictionary<Key, Value> IntersectWith<Key, Value>(this MultiDictionary<Key, Value> @this, MultiDictionary<Key, Value> other)
        {
            List<Key> keys = @this.GetKeys().ToList();
            foreach (Key key in keys)
            {
                if (!other.GetOrDefault(key).Any())
                    @this.RemoveKey(key);
            }

            foreach (Key key in @this.GetKeys())
            {
                List<Value> toRemove = @this.GetOrDefault(key).Where(value => !other.Get(key).Contains(value)).ToList();
                foreach (Value value in toRemove) { @this.Remove(key, value); }
            }

            return @this;
        }

        public static MultiDictionary<Key, Value> UnionWith<Key, Value>(this MultiDictionary<Key, Value> @this, MultiDictionary<Key, Value> other)
        {
            foreach (Key key in other.GetKeys())
            {
                foreach (Value value in other.Get(key))
                {
                    @this.Add(key, value);
                }
            }
            return @this;
        }

        public static MultiDictionary<Key, Value> ExceptWith<Key, Value>(this MultiDictionary<Key, Value> @this, MultiDictionary<Key, Value> other)
        {
            foreach (Key key in other.GetKeys())
            {
                foreach (Value value in other.Get(key))
                {
                    @this.Remove(key, value);
                }
            }
            return @this;
        }
    }
}
