using System;

namespace Degr 
{
	class Degree 
	{
		static void stpn() 
		{
			Console.Write("Enter ur number: ");
			int num = Convert.ToInt32(Console.ReadLine());
			Console.Write("Enter degree: ");
			int tmp = Convert.ToInt32(Console.ReadLine());
			bool flag = false;

			if(tmp == 0) {
				Console.WriteLine("Result = 1");
				System.Environment.Exit(1);
			} else if(num < 0) {
				if(tmp % 2 != 0) flag = true;
				num *= -1;
			}

			int self_add_result = num;
			int mult_value = num;
			for(int i = 0; i < tmp-1; i++) {
				for(int j = 0; j < num-1; j++) {
					self_add_result += mult_value;
				}
				mult_value = self_add_result;
			}
			if(flag == true) mult_value *= -1;
			Console.WriteLine("Result = " + mult_value);
		}
		static void Main() 
		{
			stpn();
		}
	}	
}
