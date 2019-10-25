
public class Student extends Person{
	private String[] classes;
	
	public Student(String n, int a, String[] c){
		super(n,a);
		this.classes = c;
	}
	
	public String toString(){
		//Overwite toString from parent and add new detail to it.
		String repr = super.toString() + "\nClasses: \n";
		for (int i = 0; i < classes.length; i++){
			repr += classes[i] + "\n";
		}
		return repr;
	}
	
	public static void main(String[] args){
		String[] classes = new String[]{"Python programming", "Programming Design","IT Project Management"};
		Student s = new Student("Wang MangMang",34,classes);
		//s.age = 19;
		s.setAge(100);
		System.out.println(s);
	}
}