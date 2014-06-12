import java.util.ArrayList;
import java.util.Hashtable;

public class Solver
{
	static Hashtable<ArrayList<Boolean>, Boolean> solutions;
	static int count;

	public static int soma(ArrayList<Integer> set, ArrayList<Boolean> marks, boolean flag)
	{
		int soma = 0;
		for (int i = 0; i < set.size(); i++)
		{
			if (marks.get(i) == flag)
			{
				soma += set.get(i);
			}
		}
		return soma;
	}
	
	public static void algorithm(int half, ArrayList<Integer> set, ArrayList<Boolean> marks, int index)
	{
		if (!solutions.containsKey(marks))
		{
			marks.set(index, true);
			solutions.put(marks, true);
			int soma = soma(set, marks, true);
			if (soma > half)
				return;
			if (soma == soma(set, marks, false))
			{
				count++;
				return;
			}
			for (int i = index + 1; i < set.size(); i++)
			{
				algorithm(half, new ArrayList<>(set), new ArrayList<>(marks), i);
			}
		}
	}
	
	public static void main(String[] args)
	{
		solutions = new Hashtable<>();
		count = 0;
		ArrayList<Integer> set = new ArrayList<>(args.length);
		int max = 0;
		int sum = 0;
		for (int i = 0; i < args.length; i++)
		{
			set.add(Integer.parseInt(args[i]));
			sum += Integer.parseInt(args[i]);
			if (max < Integer.parseInt(args[i]))
			{
				max = Integer.parseInt(args[i]);
			}
		}
		
		System.out.println("Conjunto: " + set.toString());
		
		if (sum % 2 == 0)
		{
			int half = sum / 2;
			if (max <= half)
			{
				ArrayList<Boolean> blabla= new ArrayList<>();
				for (int i = 0; i < set.size(); i++) {
					blabla.add(false);
				}
				algorithm(half, set, blabla, 0);
				System.out.println(count);
			}
			else
			{
				System.out.println("Not found D:");	
			}
		}
		else
		{
			System.out.println("Not found D:");
		}
	}
}
