## How can I parse this type?

```c
int (*(*f[5])(double))[10];
```

## Answer

Here's how to parse that monstrosity without summoning dark spirits.

We'll use the standard human method: **start at the identifier, then expand outward, respecting parentheses** (a.k.a. the "clockwise/spiral rule"). The key is: **`[]` and `()` bind tighter than `*`** unless parentheses force otherwise.

Your declaration:

```c
int (*(*f[5])(double))[10];
```

## Step-by-step parse

### 1) Find the name

The identifier is **`f`**.

So: "`f` is …"

---

### 2) Look immediately right of `f`

You see:

```c
f[5]
```

So: **`f` is an array of 5 …**

(Currently: `f` = array[5] of ???)

---

### 3) Now look immediately left of that `f[5]`

You have:

```c
(*f[5])
```

So: **`f` is an array of 5 pointers to …**

(Currently: `f` = array[5] of pointer to ???)

---

### 4) Now move outward again: to the right of `(*f[5])`

You see:

```c
(*f[5])(double)
```

That means you are "calling" what the pointer points to, so it's a function:

So: **`f` is an array of 5 pointers to functions taking a `double` and returning …**

(Currently: `f` = array[5] of pointer to function(double) returning ???)

---

### 5) Now move outward: left of `(*f[5])(double)`

You see another `*`:

```c
(*(*f[5])(double))
```

So the function returns a pointer:(

So: **… returning a pointer to …**

(Currently: `f` = array[5] of pointer to function(double) returning pointer to ???)

---

### 6) Now move outward: right of that whole `(*(*f[5])(double))`

You see:

```c
(*(*f[5])(double))[10]
```

That means the pointer points to an array of 10:

So: **… returning a pointer to an array of 10 …**

(Currently: `f` = array[5] of pointer to function(double) returning pointer to array[10] of ???)

---

### 7) Finally, apply the base type at the far left

The base type is `int`.

So the array[10] contains `int`.

## Final plain-English meaning

**`f` is an array of 5 pointers to functions that take a `double` and return a pointer to an array of 10 `int`s.**

If you want it more "type-ish":

* `f` : array(5) of pointer to function(double) -> pointer to array(10) of int

Or, with a typedef-style mental rewrite:

```c
// return type: pointer to array[10] of int
typedef int (*Ret)[10];

// f: array[5] of pointer to function(double) returning Ret
Ret (*f[5])(double);
```

Yes, it's hideous. But now you can read it, which is basically a superpower in C.
