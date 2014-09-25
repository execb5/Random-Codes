import java.io.*;

public class HDDOperations<E>
{
	
	public void saveObjectData(E thing, String name)
	{
		try
		{
			FileOutputStream fos = new FileOutputStream(name);
			ObjectOutputStream ios = new ObjectOutputStream(fos);
			ios.writeObject(thing);
			ios.close();
			fos.close();
		}
		catch (IOException e)
		{
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}
	
	public E readObjectData(String name)
	{
		E thing = null;
		try
		{
			FileInputStream fis = new FileInputStream(name);
			ObjectInputStream ois = new ObjectInputStream(fis);
			thing = (E) ois.readObject();
			ois.close();
			fis.close();
		}
		catch (IOException e)
		{
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		catch (ClassNotFoundException e)
		{
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		return thing;
	}
}
