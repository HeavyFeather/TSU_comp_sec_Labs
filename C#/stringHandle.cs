using System;

namespace stringHandl 
{
        class stringHandle 
        {
		static void symCount()
                {
                        string text = "";
                        Console.Write("Your string 's' = ");
			text = Console.ReadLine();
			Console.Write("Your 'c' = ");
			char c = Convert.ToChar(Console.ReadLine());
			int i = 0;
			foreach(char sym in text) {
				if(c == sym) i++;   
			}
			
			Console.WriteLine("Count of '" + c + "' : " + i);
                }

		static void delNumb()
		{
			string text = "";
                        Console.Write("Your string 's' = ");
                        text = Console.ReadLine();
			for(int sym = 48; sym <= 57; sym++) {
			text = text.Replace(Convert.ToString(Convert.ToChar(sym)), "");
			}
			Console.WriteLine(text);
		}

		static void findKey()
		{
			string key = "key";
                        string text = "";
                        Console.Write("Your string 's' = ");
			text = Console.ReadLine();
			foreach(char sym in text) {
				foreach(char c in key) {
					if(c == sym) key = key.Replace(Convert.ToString(sym), "");
				}
			}
			if(key == "") {
				Console.WriteLine("[+] True");
				return;
			}
			Console.WriteLine("[-] False");
		}

		static void brackCheck()
		{
			string text = "";
                        Console.Write("Your string 's' = ");
			text = Console.ReadLine();
			int flag = 0;
			
			foreach(char sym in text) {
				if(Convert.ToString(sym) == ")") {
					flag--;
					if(flag < 0) {
						Console.WriteLine("[-] False");
						return;
					}
				}
				else if(Convert.ToString(sym) == "(") flag++;
				}
			
			if(flag > 0) { 
				Console.WriteLine("[-] False");
				return;
			}
			
			Console.WriteLine("[+] True");
		}

                static void Main()
                {
			symCount();
			delNumb();
			findKey();
			brackCheck();
                }
        }
}
