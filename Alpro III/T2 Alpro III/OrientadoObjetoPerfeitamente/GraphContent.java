/*
 * Created on 4 Nov 2013 23:40:02
 */

/**
 * @author ingrid
 *
 */
public interface GraphContent<T> {
	
	public boolean isNext(T other);
	
	public boolean isPrevious(T other);

}
