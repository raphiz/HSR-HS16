# Delegates & Events

Delegates und Events sind "convenience"-Features, welche nicht mächtiger sind als bsp. Interfaces, aber wesentlich Bequemer. Delegates sind primär wichtig zu verstehen, da sie ein evolutionärer Vorgänger in C# von Lambdas sind.

## Delegates

Delegates sind eine Art "Function Pointer" und können etwas mit Anonymen Klassen in Java verglichen werden. Folglich sind Delegates Referenztypen.

Delegate
: Typ, definiert Name und Signatur

Delegate Instanz
: "Methodenzeiger"

Multicast-Delegates
: Mehrere Instanzen in einfach verketteter List


### Deklaration

```csharp

// 1. Deklaration eines Delegate-Typs
public delegate void Notifier(string sender);

class Examples {
     public void Test()
     {
         // 2. Deklaration Delegate-Variable
         Notifier greetings;
         // 3. Zuweisung einer Methode
         greetings = new Notifier(SayHello);
         //    oder in der Kurzform
         greetings = SayHello;
         // 4. Aufruf einer Delegate-Variable
         greetings("John");
      }
      private void SayHello(string sender) {
          Console.WriteLine("Hello {0}", sender);
      }
}
```

Bei der Zuweisung kann irgend eine Methode (statisch oder auf einem Objekt) angegben werden, auf die die Signatur des Delegates passt. Im Beispiel also
eine Methode mit Rückgabewert void und einem String als Parameter.

```csharp
greetings = SayHello;
greetings = Console.WriteLine;
```

Es gibt aber einige Einschränkungen:

* Die Methode darf `static`, `virtual`, `override` und/oder `new` sein
* Die Methode darf *nicht* `abstract` sein
* Die Methodensignatur muss auf das Delegate passen:
    * Gleiche Anzahl Parameter
    * Gleiche Parametertypen/Rückgabetyp
    * Gleiche Parameterarten (`ref`, `out`, value)

!!! warning

    Die Deklaration des Delegate-Types ist auf Namespace-Level, da es sich
    um einen eigenständigen Typ handelt!

!!! warning

    Zuweisung von `null` ist erlaubt! Ensprechend kann beim Aufrunf des Delegates eine NullReferenceException geworfen werden. Daher immer ein Null-Check machen!

### Multicast Delegates
Jeder Delegatey-Typ ist ein Mutlicast Delegate, was bedeutet, dass jeder Delegate-Variable **beliebig viele methoden-Referenzen zugewiesen werden können**.

Die Ausführung erfolgt in gleicher Reihenfolge des Hinzufügens.

```csharp
Notifier greetings = SayHello;
greetings += SayHello;
greetings += SayGoodBye;
greetings += SayHello;
greetings -= SayHello;

// Resultat:
// SayHello("John");
// SayHello("John");
// SayGoodBye("John");

```

Hat ein Delegate einen Rückgabewert, so wird derjenige Rückgababewert des Letzten Aufrufs zurückgegeben. Das Gleiche gilt für `out`- und `ref`-Parameter

### Hinter der Kulisse

Das Delegate merkt sich das target (das Objekt/die Klasse, auf dem die Methode deklariert ist), die Methode sowie das Vorherige Element (prev) (analog LinkedList). Prev ermöglicht also, dass mehrere Methoden einem Delegate zugewiesen werden können.

```csharp
public delegate void Notifier(string sender);
```

wird vom Compiler zu

```csharp
public sealed class Notifier : MulticastDelegate {
    public Notifier(object obj, int method) { }
    public virtual void Invoke( string sender) { }
    public virtual IAsyncResult BeginInvoke(
        string sender,
        AsyncCallback callback,
        object obj) { }
    public virtual void EndInvoke( IAsyncResult result){ }
}
```

Aus dem Aufruf

```csharp
greetings("John");
```

macht der Compiler:

```csharp
foreach(Delegate del in greetings.GetInvocationList())
{
    ((Notifier)del)("John");
}
```

* Pro: Statische methoden
* Contra: Nur genau eine Methode (bei Interface meherer)
* Da null sein kann: Null-Check "Pattern" - bzw. delegatevar?.Invoke(params);

!!! seealso

    * Vergleich Interfaces vs. Delegates - Vorlesung Woche 5, Folie Nr. 11
    * Beispiele von Delegates - Vorlesung Woche 5, Folie Nr. 22-31


### Weiteres
Delegates können auch zusammengefügt werden:

```csharp
Notifier n1 = SayHello;
Notifier n2 = SayGoodBye;
Notifier c1 = n1 + n2;
// analog zu
Notifier c1 = (Notifier)Delegate.Combine(n1, n2);
```

### Vordefinierte Generic Delegates

Action: 0-n Parameter mit void als Rückgabewert.

```
public delegate void Action();
public delegate void Action<in T>(T obj);
public delegate void Action<in T1, in T2>(T1 obj1, T2 obj2);
[...]
public delegate void Action<in T1, ..., in T16>(T1 obj1,..., T16 obj16);
```

`Func`: Funktion mit 0 – n Parametern - `TResult` als Rückgabewert

```csharp
public delegate TResult Func<out TResult>();
public delegate TResult Func<in T, out TResult>(T arg);
public delegate TResult Func<in T1, in T2, out TResult>(T1 arg1, T2 arg2);
[...]
public delegate TResult Func<in T1, ..., in T16, out TResult>(T1 arg1,..., T16 arg16);
```

`Predicate`: Prädikat mit 1 Parameter «bool» als Rückgabewert

```csharp
public delegate bool Predicate<in T>(T obj);
```

## Events

Events sind ein reines Compiler-Feature, als syntactic Sugar.

Event
: Compiler-generierte Delegate Instanz
: mit public += und -= Methoden
: restliche Methoden privat


Beispiel:

```csharp
public delegate void TickEventHandler (int ticks, int interval);
public class Clock
{
    public event TickEventHandler OnTickEvent;

    // Implementierung
    private void Tick(object sender, EventArgs e) {
        ticks++;
        OnTickEvent?.Invoke(ticks, interval);
    }
}
```

macht der Compiler zu:

```csharp
public delegate void TickEventHandler (int ticks, int interval);
public class Clock
{
    private TickEventHandler OnTickEvent;

    public void add_OnTickEvent(TickEventHandler h)
    {
        OnTickEvent += h;
    }
    public void remove_OnTickEvent(TickEventHandler h)
    {
      OnTickEvent -= h;
    }
    private void Tick(object sender, EventArgs e) {
        ticks++;
        OnTickEvent?.Invoke(ticks, interval);
    }
}
```

Somit kann man ganz bequem events wie folgt hinzufügen (und analog dazu entfernen)

```csharp
ClockObserver t1 = new ClockObserver("O1");
c1.onTickEvent += t1.OnTickEvent;
```

### Best practices

Um in Frameworks gute wartbarkeit zu erlangen sollte:

* der return Type eines Events immer void sein
* der 1. Parameter der Sender des Events sein
* der 2. Parameter der Event typ EventArgs sein, welche von EventArgs ableitet

```csharp
public delegate void ClickEventHandler(object sender, ClickEventArgs e);

public class ClickEventArgs : EventArgs
{
    public string MouseButton{ get; set; }
}

public class Button
{
    public event ClickEventHandler OnClick;
}
```

## Anonyme Methoden

Anonyme Methoden können dann Verwendet werden, we die deklaration einer speziellen Methoden nicht sinnvoll ist (siehe Lambdas). Closure sind auch möglich - sind aber auch ein reines Compiler Feature.


```csharp
list.ForEach(delegate(int i)
    { Console.WriteLine(i); }
);
```
