// public class Person{
// 	private String name;
// 	private int age;
//
// 	public Person(String n, int a){
// 		this.name = n;
// 		this.age = a;
// 	}
//
// 	public String toString(){
// 	return ("Name: " + this.name + "\tAge: " + this.age);
// 	}
//
// 	public static void main(String[] args){
// 		Person p1 = new Person("Francis", 21);
// 		Person p2 = new Person("Catherine", 23);
//
// 		System.out.println(p1);
// 		System.out.println(p2);
// 	}
// }

public class Person{
	private String name;
	private int age;
	
	public Person(String n, int a){
		this.name = n;
		this.age = a;
	}
	
	public void setAge(int g){
		if (g < 0 || g > 120){	//Reasonable age range for humans
			System.out.println("Age still remain: " + this.age);
			//Do not allow negative or stupid age changes
			return;
		}
		this.age = g;
	}
	
	public String toString(){
	return ("Name: " + this.name + "\tAge: " + this.age);
	}
	
//	public static void main(String[] args){
//		Person p1 = new Person("Francis", 21);
//		Person p2 = new Person("Catherine", 23);
//		//p1.age = -1;	//will work because main is in the same class. When moved out to student, it wont work
//		we must use the setter method to do it...  Example of data hiding in Java
//		p1.setAge(-1);
//		System.out.println(p1);
//		System.out.println(p2);
//	}
}