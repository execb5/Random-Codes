public class T1
{
	public static final int CREW = 11;
	//public static final int MONKEY_FINAL = 6;

	public static void main(String[] args)
	{
		for (long monkey = 1; monkey < 7; monkey++)
		{
			long mulberrys = 0;
			//long monkey = MONKEY_FINAL;
			long remaining = 0;
			long morningMullberry;
			long begin = System.currentTimeMillis();
			for (remaining = 1; ; remaining++)
			{
				mulberrys = remaining * CREW;
				morningMullberry = mulberrys;
				boolean ok = true;
				for (int t = 0; t < CREW; t++)
				{
					if (mulberrys % (CREW - 1) != 0)
					{
						ok = false;
						break;
					}
					long individualPart = mulberrys / (CREW - 1);
					mulberrys += individualPart + monkey;
				}
				if (ok)
				{
					break;
				}
			}
			long end = System.currentTimeMillis();
			System.out.println("Crew: " + CREW);
			System.out.println("Monkey: " + monkey);
			System.out.println("Mulberrys " + mulberrys);
			System.out.println("MorningMullberry: " + morningMullberry);
			System.out.println(end - begin + "ms");
			for (int i = 1; i <= CREW; i++)
			{
				System.out.println("T" + i + ": " + (mulberrys/CREW + morningMullberry/CREW));
				mulberrys = mulberrys - mulberrys/CREW - monkey;
			}
			System.out.println();
		}
	}
}