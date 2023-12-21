class Program
{
    static void Main()
    {
        //testList();
        //testMnojestvo();
    }

    static void testList()
    {
        Node x = new Node(12);
        x.print();
        LinkedList list = new LinkedList(1);
        for(int i = -1; i < 12; i++){
            list.AddLast(i);
        }
        LinkedList l = new LinkedList(1120);
        for(int i = 12; i < 20; i++){
            l.AddLast(i);
        }
        LinkedList a = new LinkedList(1);

        a.input();
        a.print();

        LinkedList b = new LinkedList(1);

        b.input();
        b.print();

        Console.WriteLine(a != b);
        Console.WriteLine(a[0]);
        Console.WriteLine(" ");

        a.Sort();
        a.print();

        list.print();
        list.AddHead(123);
        list.print();
        list.add_to_pos(-10213,8);
        list.print();
        Console.WriteLine(list.size_list());
        list.add_after_key(-2222 ,-10213);
        list.print();
        list.remove_head();
        list.remove_tail();
        list.remove_to_pos(6);
        list.remove_to_key(-10213);
        list.add_to_pos(-12345, 8);
        list.print();
        list.min_node();
        list.Clear();
        Console.WriteLine(list.find(-103213));
        list.Sort();
        list.print();
        Console.WriteLine(list + l);
        Console.WriteLine(list);
        Console.WriteLine(list == list);
        if(list == l) Console.WriteLine("True");
             else Console.WriteLine("False");
        Console.WriteLine(list[1]);
        Console.WriteLine(list == l);
        l = list + l;
        Console.WriteLine(list.find(1314));
        int u = list[13243];
        Console.WriteLine(x);
        l.print();
       
    }

    static void testMnojestvo()
    {


        Mnojestvo s1 = new Mnojestvo();

        s1.AddRnd(10);
        s1.print();

        Console.WriteLine("1)Создайте множество S1, из 10 случайных чисел. Выведите S1 на экран (используя функцию Print).");

        //2)Создайте множество S2 и инициализируйте его (при создании) значением S1.  Выведите S2 на экран (используйте потоковый вывод). Проверьте равенство множеств S1  и  S2.


        Mnojestvo s2 = s1;

        //s2.print();

        Console.WriteLine(s1 == s2);

        Console.WriteLine("2)Создайте множество S2 и инициализируйте его (при создании) значением S1.  Выведите S2 на экран (используйте потоковый вывод). Проверьте равенство множеств S1  и  S2.");

        //3)Проверьте, есть ли в S1 элемент 5. Создайте множество S3, которое получается  удалением/добавлением из S1 элемента 5. Проверьте, что S1 и S3 – не равны.



        Node x = s1.find(5);

        Console.WriteLine(x.print());


        Mnojestvo s3 = new Mnojestvo(s2);

        //s3 = s2;
        //s3.remove_el_set(5);
        s3.AddLast(5);

        s3.print();
        s2.print();

        Console.WriteLine("3)Проверьте, есть ли в S1 элемент 5. Создайте множество S3, которое получается  удалением/добавлением из S1 элемента 5. Проверьте, что S1 и S3 – не равны.");


        //4)Создайте пустое множество S4. Проверьте его на пустоту.  Добавьте в S4 последовательно числа 5, 10, 15, 5.  Выведите S4 на экран.

        Mnojestvo s4 = new Mnojestvo();

        s4.Check_For_Emptiness();

        s4.AddHead(43);
        s4.AddLast(10);
        s4.AddLast(15);
        s4.AddLast(5);
        s4.print();

        Console.WriteLine("4)Создайте пустое множество S4. Проверьте его на пустоту.  Добавьте в S4 последовательно числа 5, 10, 15, 5.  Выведите S4 на экран.");

        //5)Создайте пустое множество S5.  Инициализируйте его множеством S4.  Проверьте, что во множестве S5 есть элемент 15 и удалите его. Выведите получившееся множество на экран.


        Mnojestvo s5 = new Mnojestvo(s4);

        Node _x = s5.find(15);
        Console.WriteLine(_x.print());
        //s5.remove_el_set(15);
        s5.print();

        Console.WriteLine("5)Создайте пустое множество S5.  Инициализируйте его множеством S4.  Проверьте, что во множестве S5 есть элемент 15 и удалите его. Выведите получившееся множество на экран.");

        //6)Создайте список T, из 20 случайных чисел. Выведите T на экран. Создайте из T множество S6.  Выведите S6 на экран. Определите количество элементов в S6.

        //Mnojestvo T = new Mnojestvo();
        LinkedList T = new LinkedList();
        T.AddRnd(30);
        //Console.WriteLine("sdfF");
        T.print();

        Mnojestvo s6 = new Mnojestvo(T);
        //s6 = T;
        s6.print();
        Console.WriteLine(s6.size_list());

        Console.WriteLine("6)Создайте список T, из 20 случайных чисел. Выведите T на экран. Создайте из T множество S6.  Выведите S6 на экран. Определите количество элементов в S6.");

        //7)Найдите S7 – дополнение S6 до универсального. Найдите множество S8=S7∩S6.



        Mnojestvo s7 = new Mnojestvo();
        s7.AddRnd(10);

        s7 = s7.Complement(s6);

        // //s7.AddHead(-1);
        // //s7 = s7.Complement(s6);

        // Console.WriteLine(" EF");

        Mnojestvo s8 = new Mnojestvo();
        //Mnojestvo s9 = new Mnojestvo();
        s8 = s7.Intersection_Of_Set(s6);
        //s9.AddRnd(5);
        //s8.print();
        //s9.print();

        //s8.Intersection_Of_Set(s9);

        Console.WriteLine("7)Найдите S7 – дополнение S6 до универсального. Найдите множество S8=S7∩S6.");


        //8)Создайте множество S9={1,3,5,7,9,11,13,15,17,19,21,23,25,27,29} (используйте потоковый ввод).  Найдите V1 =S7 ∩ S9,  V2 = S7 ∪ S9,  V3 = S7 \ S9.


        Mnojestvo s9 = new Mnojestvo();
        s9.AddRnd(9);
        //s10.Add();//потоковый ввод
        Mnojestvo v1 = new Mnojestvo();
        s7.print();
        s9.print();
        v1 = s7.Intersection_Of_Set(s9);
        v1.print();
        Mnojestvo v2 = new Mnojestvo();
        v2 = s7.unite(s9);

        Mnojestvo v3 = new Mnojestvo();
        v3 = s7.Set_Difference(s9);


        Console.WriteLine("8)Создайте множество S9={1,3,5,7,9,11,13,15,17,19,21,23,25,27,29} (используйте потоковый ввод).  Найдите V1 =S7 ∩ S9,  V2 = S7 ∪ S9,  V3 = S7 '\' S9.");


        //9)Измените V1, объединив его с V3. Сравните V1  с S7.

        v1 = v1.unite(v3);
        Console.WriteLine(v1 == s7);

        Console.WriteLine("9)Измените V1, объединив его с V3. Сравните V1  с S7.");


        //10)Измените множество V2, заменив его разностью V2 и V3. Сравните V2  с  S9


        v2 = v2.Set_Difference(v3);
        Console.WriteLine(v2 == s9);

        Console.WriteLine("10)Измените множество V2, заменив его разностью V2 и V3. Сравните V2 с S9");

        // Mnojestvo s9 = new Mnojestvo();
        // s9.AddRnd(20);
        // //s9.print();

        // Mnojestvo s8 = new Mnojestvo(s9);
        // s9.AddLast(5);
        // s8.remove_el_set(5);
        // s9.print();

        // s8.print();
        // s8.AddHead(-1);
        // s8.print();
        // s9.print();


        //s9.unite(s10);



        //s7.print();



        // Mnojestvo a = new Mnojestvo(12);
        // a.Add();
        // a.remove_el_set(55);
        // Console.WriteLine(" ");
        // a.print();


        // Mnojestvo d = new Mnojestvo(13);

        // d.Add();


        // // a.unite(d);

        // //a.Intersection_Of_Set(d);
        // //a.Set_Difference(d);
        // a.Complement(d);

        //a.Add_Element_To_Set();
        //a.print();

        // Mnojestvo A = new Mnojestvo();
        // A.Add();

        // Mnojestvo B = new Mnojestvo();
        // B.Add();

        // Console.WriteLine(A == B);
    }
}


class Node
{
    int data;
    public int Data
    {
        get 
        { 
            return data; 
        }
        set
        {
            data = value;
        }
    }
    Node next;
    public Node Next
    {
        get
        {
            return next;
        }
        set
        {
            next = value;
        }
    }

    public Node(int data)
    {
        Data = data;
    }

    public int print()
    {
        if (Data == -1) return -1;
        return Data;
    }
}



class LinkedList
{
    public int this[int index]
    {
        get
        {
            Node current = Head;
            for (int i = 0; i < index && current != null; i++)
            {
                current = current.Next;
            }
            if (current == null)
            {
                throw new IndexOutOfRangeException();
            }
            return current.Data;
        }
    }


    public static bool operator ==(LinkedList l1, LinkedList l2)
    {

        Node current1 = l1.Head;
        Node current2 = l2.Head;
        while (current1?.Next != null && current2?.Next != null)
        {
            current1 = current1.Next;
            current2 = current2.Next;

            if (current1.Data != current2.Data)
            {

                return false;
            }
        }
        return true;
    }

    public static bool operator !=(LinkedList l1, LinkedList l2)
    {
        return !(l1 == l2);
    }

    public override bool Equals(object o)
    {
        if (o == null || !(o is LinkedList))
        {
            return false;
        }
        return this == (LinkedList)o;
    }

    public override int GetHashCode()
    {
        return base.GetHashCode();
    }


    public static LinkedList operator +(LinkedList A, LinkedList B)
    {
        Node current_B = B.Head;

        while (current_B.Next != null) current_B = current_B.Next;

        //Console.WriteLine(current_A.Data);
        //Console.WriteLine(current_B.Data);

        current_B.Next = A.Head;


        return B;

    }

    //в хвост
    // public static LinkedList operator +(LinkedList A, LinkedList B){


    //     Node current_A = A.Head;
    //     Node current_B = B.Head;

    //     while(current_A.Next != null) current_A = current_A.Next;

    //     //Console.WriteLine(current_A.Data);
    //     //Console.WriteLine(current_B.Data);

    //     current_A.Next = B.Head;


    //     return A;
    // }

    // public static int operator + (LinkedList A, int key){

    //     Node node = new Node(key);
    //     node.Next = A.Head;
    //     A.Head = node;

    //     return 1;
    // }
    /*public static int operator + (LinkedList A, LinkedList B){
        //A.print();
        //B.print();
        
        //Node current = A.Head;
        Node currentt = B.Head;
        
        //Console.WriteLine(current.Data);
        //Console.WriteLine(currentt.Data);
        
        
        A.Clear();
        A.AddHead(currentt.Data);
        for(int i = 0; i < B.size_list(); i++){
            currentt = currentt.Next;
            A.AddLast(currentt.Data);
        }
        
        
        //A.print();
        return 0;
    }*/


    public void AddRnd(int count)
    {
        Random rnd = new Random();
        int _value = rnd.Next(0, 100);
        Head = new Node(_value);

        for (int i = 1; i < count; i++)
        {
            int value = rnd.Next(0, 100);
            AddLast(value);
        }
    }

    public Node Head;
    //Node tail;
    //int count;

    public LinkedList(int headData)
    {
        Head = new Node(headData);
    }



    public LinkedList() { }


    //добавление в голову

    public void AddHead(int data)
    {
        Node node = new Node(data);
        node.Next = Head;
        Head = node;
    }

    //добавление в хвост
    public void AddLast(int data)
    {
        Node current = Head;

        while (current.Next != null) current = current.Next;
        current.Next = new Node(data);
    }


    //добавление на позицию

    public void add_to_pos(int data, int k)
    {
        Node node = new Node(data);
        Node current = Head;
        Node? prev = null;

        for (int i = 0; i < size_list(); i++)
        {
            if (i == k)
            {

                prev.Next = node;
                node.Next = current;

                //Console.WriteLine(prev.Data);
                //Console.WriteLine(current.Data);
                break;
            }
            prev = current;
            current = current.Next;
            //Console.WriteLine(prev.Data);
            //Console.WriteLine(current.Data);
        }
    }

    //после ключа

    public void add_after_key(int data, int key)
    {
        Node node = new Node(data);
        Node current = Head;
        Node currentNext = null;

        for (int i = 0; i < size_list(); i++)
        {
            if (key == current.Data)
            {

                //current = node;
                //node = current.Next;

                current.Next = node;
                node.Next = currentNext;

                //Console.WriteLine(current.Data);
                //Console.WriteLine(currentNext.Data);
                //Console.WriteLine(node.Data);
                break;
            }
            current = current.Next;
            currentNext = current.Next;
        }

    }


    public void remove_head()
    {
        Head = Head.Next;
    }

    //удаление хвоста

    public void remove_tail()
    {
        Node current = Head;

        while (current.Next.Next != null) current = current.Next;

        current.Next = null;
        //Console.WriteLine(current.Data);
    }

    //удаление по позиции

    public void remove_to_pos(int k)
    {
        Node current = Head;
        Node prev = null;

        for (int i = 0; i < size_list(); i++)
        {
            if (i == k)
            {

                prev.Next = current.Next;

                //Console.WriteLine(prev.Data);
                //Console.WriteLine(current.Next.Data);
                break;
            }

            prev = current;
            current = current.Next;

        }
    }


    //удаление по ключу

    public void remove_to_key(int key)
    {
        Node current = Head;
        Node prev = null;

        while (current.Next != null)
        {
            if (current.Data == key)
            {
                prev.Next = current.Next;
                break;
            }

            prev = current;
            current = current.Next;
        }

        //Console.WriteLine(current.Data);
    }

    //max

    public void max_node()
    {
        Node current = Head;
        int max = current.Data;

        while (current != null)
        {
            if (current.Data > max)
            {
                max = current.Data;
            }
            current = current.Next;
        }

        Console.WriteLine(max);

    }

    //min 

    public void min_node()
    {
        Node current = Head;
        int max = current.Data;

        while (current != null)
        {
            if (current.Data < max)
            {
                max = current.Data;
            }
            current = current.Next;
        }

        Console.WriteLine(max);

    }





    //clean list

    public void Clear()
    {
        Head = null;
    }

    //chek list
    public bool check(){
        Node current = Head;
        if (Head == null) return true;
        return false;
    }


    //find

    public Node find(int key)
    {
        Node current = Head;

        while (current != null)
        {
            if (current.Data == key)
            {
                //Console.WriteLine(current.Data);
                return current;
            }
            current = current.Next;
        }
        Node tmp = new Node(-1);
        //tmp.Data = -1;

        return tmp;
    }


    //размер списка

    public int size_list()
    {
        if (Head == null) return 0;
        Node current = Head;

        int i = 0;
        while (current.Next != null)
        {
            current = current.Next;
            i++;
        }

        return i + 1;
    }

    public void print()
    {
        Node current = Head;

        while (current != null)
        {
            Console.Write(current.Data + " ");
            current = current.Next;
        }

        Console.WriteLine();
    }

    public void input()
    {
        Node current = Head;
        Console.Write("Enter a size list: ");
        int size = Convert.ToInt32(Console.ReadLine());

        for (int i = 0; i < size; i++)
        {
            Console.Write("Enter a number: ");
            int x = Convert.ToInt32(Console.ReadLine());
            AddLast(x);
            current = current.Next;
        }



    }



    public void Sort()
    {
        if (Head == null || Head.Next == null) // уже отсортирован или пустой список
        {
            return;
        }

        Node currentNode = Head;
        Node nextNode = Head.Next;
        Node tempNode = new Node(0);
        bool swapped = true;

        while (swapped)
        {
            swapped = false;
            while (nextNode != null)
            {
                if (currentNode.Data > nextNode.Data)
                {
                    tempNode.Data = currentNode.Data;
                    currentNode.Data = nextNode.Data;
                    nextNode.Data = tempNode.Data;
                    swapped = true;
                }
                currentNode = currentNode.Next;
                nextNode = nextNode.Next;
            }
            currentNode = Head;
            nextNode = Head.Next;
        }
    }
}


class Mnojestvo : LinkedList
{
    public int P = 0;
    //public LinkedList llist = new LinkedList(-11);
    public Mnojestvo(int headData) : base(headData) { }
    public Mnojestvo() : base() { }


    public Mnojestvo(Mnojestvo other)
    {
        Head = new Node(other.Head.Data);
        Node current = other.Head.Next;

        while (current != null)
        {
            int tmp = current.Data;
            AddLast(tmp);
            current = current.Next;
        }
    }

    public Mnojestvo(LinkedList other)
    {
        Head = new Node(other.Head.Data);
        Node current = other.Head.Next;

        while (current != null)
        {
            int tmp = current.Data;
            AddLast(tmp);
            current = current.Next;
        }
    }

    public void Check_For_Emptiness()
    {
        if (size_list() == 0)
        {
            Console.WriteLine("Список пустой");
        }
    }


    public void _input()
    {
        Console.Write("Enter a size list: ");
        int size = Convert.ToInt32(Console.ReadLine());
        //Console.WriteLine(size);

        Console.Write("Enter a head: ");
        int tmp = Convert.ToInt32(Console.ReadLine());
        Head = new Node(tmp);

        Node current = Head.Next;

        for (int i = 1; i < size; i++)
        {
            Console.Write("Enter a number: ");
            int x = Convert.ToInt32(Console.ReadLine());

            for (int j = 0; j < size - i; i++)
            {
                if (current.Data == x)
                {
                    i--;
                    Console.WriteLine("Данный элемент уже присутствует!");
                    break;
                }
            }

            AddLast(x);
            current = current.Next;
        }

    }


    public void Add()
    {
        Console.Write("Enter a size list: ");
        int size = Convert.ToInt32(Console.ReadLine());

        Console.Write("Enter a head: ");
        int tmp = Convert.ToInt32(Console.ReadLine());
        Head = new Node(tmp);


        for (int i = 0; i < size - 1; i++)
        {
            Console.Write("Enter a number: ");
            int x = Convert.ToInt32(Console.ReadLine());
            if (Find(x) != null)
            {
                Console.WriteLine($"Элемент {x} уже существует в списке. Введите другое значение:");
                i--;
                continue;
                //AddLast(x);
                // Node newNode = new Node(x);
                // newNode.Next = Head;
                // Head = newNode;
            }
            else
            {
                AddLast(x);
                // Node newNode = new Node(x);
                // newNode.Next = Head;
                // Head = newNode;
            }
        }
    }

    public void AddRnd(int count)
    {
        Random rnd = new Random();
        int _value = rnd.Next(0, 100);
        Head = new Node(_value);

        for (int i = 1; i < count; i++)
        {
            int value = rnd.Next(0, 100);
            if (Find(value) != null)
            {
                i--;
                continue;
            }
            else
            {
                AddLast(value);
            }
        }
    }

    public Node Find(int data)
    {
        Node current = Head;
        while (current != null)
        {
            if (current.Data == data)
            {
                return current;
            }
            current = current.Next;
        }
        return null;
    }



    // 7)	объединение 


    public Mnojestvo unite(LinkedList A)
    {
        Node currentA = A.Head;
        Node current = Head;

        Mnojestvo result = new Mnojestvo(A.Head.Data);

        // while(currentA.Next != null){
        //     result.AddLast(currentA.Data);
        // }

        // result.AddLast(15);
        // result.print();

        //Console.WriteLine(A.size_list());
        for (int i = 0; i < size_list(); i++)
        {
            result.AddLast(current.Data);
            current = current.Next;
        }

        //result.print();

        //Console.WriteLine(" | ");

        for (int i = 0; i < A.size_list(); i++)
        {
            if (Find(currentA.Data) != null)
            {

            }
            else
            {
                result.AddLast(currentA.Data);
            }
            currentA = currentA.Next;
        }

        // Console.WriteLine(size_list());

        //result.print();
        return result;
        // Console.WriteLine(currentA.Data);

        // Console.WriteLine(current.Data);

    }


    //8)	добавление элемента к множеству (создается новое множество, изменяется исходное множество)


    public void Add_Element_To_Set()
    {
        //Node current = Head;
        //LinkedList tmp = new LinkedList(current.Data);



        Console.Write("Сколько элементов добавить:  ");
        int count = Convert.ToInt32(Console.ReadLine());


        for (int i = 0; i < count; i++)
        {
            Console.Write("Enter a number: ");
            int x = Convert.ToInt32(Console.ReadLine());

            if (Find(x) != null)
            {
                Console.WriteLine($"Элемент {x} уже существует в списке. Введите другое значение:");
                i--;
                continue;
            }
            else
            {
                AddLast(x);
            }
        }


    }


    //9)	пересечение двух множеств (создается новое множество, изменяется исходное множество)


    public Mnojestvo Intersection_Of_Set(LinkedList A)
    {
        // print();
        // A.print();
        // Console.WriteLine(A.Head.Next.Data);
        // Console.WriteLine(Head.Next.Data);
        Node currentA = A.Head;
        // //Node current = Head;

        Mnojestvo tmp = new Mnojestvo(-1);
        //tmp.print();
        // tmp.AddHead(-1);

        int size = 0;
        if (size_list() > A.size_list())
        {
            size = A.size_list();
        }
        else
        {
            size = size_list();
        }

        for (int i = 0; i < size; i++)
        {
            int temp = currentA.Data;
            if (Find(temp) != null)
            {

                tmp.AddLast(temp);
            }
            currentA = currentA.Next;
        }

        // //print();
        // //Console.WriteLine(" ");
        // //A.print();
        // //Console.WriteLine(" ");
        tmp.remove_head();
        //tmp.print();
        return tmp;
    }



    //10)	разность двух множеств (создается новое множество, изменяется исходное множество)


    public Mnojestvo Set_Difference(LinkedList l2)
    {

        Node current1 = Head;
        Node current2 = l2.Head;

        Mnojestvo result = new Mnojestvo(-1);




        while (current1 != null)
        {
            bool contains = false;
            while (current2 != null)
            {
                if (current1.Data == current2.Data)
                {
                    contains = true;
                    break;
                }
                current2 = current2.Next;
            }
            if (!contains)
            {
                result.AddLast(current1.Data);
            }
            current1 = current1.Next;
            current2 = l2.Head;
        }

        result.remove_head();
        //result.print();

        return result;
    }



    // 11)	дополнение до идеального множества


    public Mnojestvo Complement(LinkedList idealSet)
    {
        //Console.WriteLine(Head.Data);
        Mnojestvo complementSet = new Mnojestvo(); // создаем новый список, который будет содержать дополнение
        complementSet.AddHead(-1);
        //Node current = Head;
        Node currentA = idealSet.Head;

        for (int i = 0; i < idealSet.size_list(); i++)
        {
            int temp = currentA.Data;
            if (Find(temp) == null)
            {
                complementSet.AddLast(temp);
            }

            currentA = currentA.Next;
        }

        complementSet.remove_head();
        complementSet.print();
        return complementSet;
    }

    //сделай дополнение до иделаьного множетсва

    public void remove_el_set(int data)
    {

        remove_to_key(data);

    }

    public static bool operator ==(Mnojestvo l1, Mnojestvo l2)
    {

        l1.Sort();
        l2.Sort();

        Node current = l1.Head;
        Node curren = l2.Head;

        for (int i = 0; i < l1.size_list(); i++)
        {
            if (current.Data != curren.Data) return false;
        }

        return true;
    }
    public static bool operator !=(Mnojestvo l1, Mnojestvo l2)
    {
        return !(l1 == l2);
    }

    // public Mnojestvo(int headData){
    //     Head = new Node(headData);
    //     Node current = Head;
    //     Console.Write("Enter a size list: ");
    //     int size = Convert.ToInt32(Console.ReadLine());

    //     for(int i = 0; i < size; i++){
    //         Console.Write("Enter a number: ");
    //         int x = Convert.ToInt32(Console.ReadLine());
    //         AddLast(x);
    //         current = current.Next;
    //     }
    // }
}


