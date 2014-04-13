/* File: hashtable.h                                     -*- C++ -*-
 * -----------------
 * This is a simple table for storing values associated with a string
 * key, supporting simple operations for Enter and Lookup.  It is not
 * much more than a thin cover over the STL associative map container,
 * but hides the awkward C++ template syntax and provides a more
 * familiar interface.
 *
 * The keys are always strings, but the values can be of any type
 * (ok, that's actually kind of a fib, it expects the type to be
 * some sort of pointer to conform to using NULL for "not found").
 * The typename for a Hashtable includes the value type in angle
 * brackets, e.g.  if the table is storing  char *as values, you
 * would use the type name Hashtable<char*>. If storing values
 * that are of type Decl*, it would be Hashtable<Decl*>.
 * The same notation is used on the matching iterator for the table,
 * i.e. a Hashtable<char*> supports an Iterator<char*>.
 *
 * An iterator is provided for iterating over the entries in a table.
 * The iterator walks through the values, one by one, in alphabetical
 * order by the key. Sample iteration usage:
 *
 *       void PrintNames(Hashtable<Decl*> *table)
 *       {
 *          Iterator<Decl*> iter = table->GetIterator();
 *          Decl *decl;
 *          while ((decl = iter.GetNextValue()) != NULL) {
 *               printf("%s\n", decl->GetName());
 *          }
 *       }
 */

#ifndef _H_hashtable
#define _H_hashtable

#include <map>
#include <string.h>

struct ltstr {
  bool operator()(const char* s1, const char* s2) const {
    return strcmp(s1, s2) < 0;
  }
};

template <class Value>
class Iterator;

template<class Value>
class Hashtable {
 private:
  std::multimap<const char*, Value, ltstr> mmap;

 public:
  // ctor creates a new empty hashtable
  Hashtable() {}

  // Returns number of entries currently in table
  int NumEntries() const;

  // Associates value with key. If a previous entry for
  // key exists, the bool parameter controls whether
  // new value overwrites the previous (removing it from
  // from the table entirely) or just shadows it (keeps previous
  // and adds additional entry). The lastmost entered one for an
  // key will be the one returned by Lookup.
  void Enter(const char *key, Value value,
             bool overwriteInsteadOfShadow = true);

  // Removes a given key->value pair.  Any other values
  // for that key are not affected. If this is the last
  // remaining value for that key, the key is removed
  // entirely.
  void Remove(const char *key, Value value);

  // Returns value stored under key or NULL if no match.
  // If more than one value for key (ie shadow feature was
  // used during Enter), returns the lastmost entered one.
  Value Lookup(const char *key);

  // Returns an Iterator object (see below) that can be used to
  // visit each value in the table in alphabetical order.
  Iterator<Value> GetIterator();
};

/* Don't worry too much about how the Iterator is implemented, see
 * sample usage above for how to iterate over a hashtable using an
 * iterator.
 */
template <class Value>
class Iterator {
  friend class Hashtable<Value>;
 private:
  typename std::multimap<const char*, Value , ltstr>::iterator cur, end;
  Iterator(std::multimap<const char*, Value, ltstr>& t)
    : cur(t.begin()), end(t.end()) {
  }

 public:
  // Returns current value and advances iterator to next.
  // Returns NULL when there are no more values in table
  // Visits every value, even those that are shadowed.
  Value GetNextValue();
};

/* Hashtable::Enter
 * ----------------
 * Stores new value for given identifier. If the key already
 * has an entry and flag is to overwrite, will remove previous entry first,
 * otherwise it just adds another entry under same key. Copies the
 * key, so you don't have to worry about its allocation.
 */
template <class Value>
void Hashtable<Value>::Enter(const char *key, Value val, bool overwrite) {
  Value prev;
  if (overwrite && (prev = Lookup(key)))
    Remove(key, prev);
  mmap.insert(std::make_pair(strdup(key), val));
}

/* Hashtable::Remove
 * -----------------
 * Removes a given key-value pair from table. If no such pair, no
 * changes are made.  Does not affect any other entries under that key.
 */
template <class Value>
void Hashtable<Value>::Remove(const char *key, Value val) {
  if (mmap.count(key) == 0) { // no matches at all
    return;
  }

  typename std::multimap<const char *, Value>::iterator itr;
  itr = mmap.find(key); // start at first occurrence
  while (itr != mmap.upper_bound(key)) {
    if (itr->second == val) { // iterate to find matching pair
      mmap.erase(itr);
      break;
    }
    ++itr;
  }
}

/* Hashtable::Lookup
 * -----------------
 * Returns the value earlier stored under key or NULL
 *if there is no matching entry
 */
template <class Value>
Value Hashtable<Value>::Lookup(const char *key) {
  Value found = NULL;
  if (mmap.count(key) > 0) {
    typename std::multimap<const char *, Value>::iterator cur, last, prev;
    cur = mmap.find(key); // start at first occurrence
    last = mmap.upper_bound(key);
    while (cur != last) { // iterate to find last entered
      prev = cur;
      if (++cur == mmap.upper_bound(key)) { // have to go one too far
        found = prev->second; // one before last was it
        break;
      }
    }
  }
  return found;
}

/* Hashtable::NumEntries
 * ---------------------
 */
template <class Value>
int Hashtable<Value>::NumEntries() const {
  return mmap.size();
}

/* Hashtable:GetIterator
 * ---------------------
 * Returns iterator which can be used to walk through all values in table.
 */
template <class Value>
Iterator<Value> Hashtable<Value>::GetIterator() {
  return Iterator<Value>(mmap);
}

/* Iterator::GetNextValue
 * ----------------------
 * Iterator method used to return current value and advance iterator
 * to next entry. Returns null if no more values exist.
 */
template <class Value>
Value Iterator<Value>::GetNextValue() {
  return (cur == end ? NULL : (*cur++).second);
}

/* vim: set ai ts=2 sts=2 sw=2 et: */
#endif
