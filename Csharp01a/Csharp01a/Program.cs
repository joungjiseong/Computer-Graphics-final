using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Csharp01a
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] intArray = { 10, 20, 30, 40, 50 };
            foreach (int arr in intArray)
                Console.Write(arr + "\t");
        }
    }
}

/*
    static void Main(string[] args)
    {
        int radius;
        double areaCalculate;
        Console.Write("반지름 입력: ");
        radius = Int32.Parse(Console.ReadLine());
        areaCalculate = 3.141592 * radius * radius;
        Console.WriteLine("반지름= {0}, 원의 면적= {1}", radius, areaCalculate);
    }

    static void Main(string[] args)
    {
        string schoolNumber;
        string studuentName;
        schoolNumber = "202004104";
        studuentName = "정지성";
        Console.WriteLine("====문자형 출력 형식====\n");
        Console.Write("학생의 학번은 \"{0}\" 이고, 이름은 \"{1}\"이다", schoolNumber,studuentName);
        Console.WriteLine();
        Console.WriteLine("학생의 학번은 \"{0}\" 이고, 이름은 \"{1}\"이다", schoolNumber, studuentName);
        Console.WriteLine("문자열 출력 자리수 : 1234567890");
        Console.WriteLine("매개변수의 자리수가 -5인 경우는 왼쪽 정렬 : {0,-5}\"", 20);
        Console.WriteLine("매개변수의 자리수가 5인 경우는 오른쪽 정렬 : {0,5}\"", 20);

        Console.WriteLine("\n====숫자형 출력 형식====\n");
        Console.WriteLine("통화형 : {0:C} {1:C5}", 99.99, 9999.9);
        Console.WriteLine("10진 정수형 : {0:D}", 99);
        Console.WriteLine("지수형 : {0:E}", 99.9);
        Console.WriteLine("고정소수점형 : {0:F3}", 99.9999);
        Console.WriteLine("10진수를 ,로 구분 : {0:N}", 99999.99);
        Console.WriteLine("16진수 표현 : {0:X4}", 999);

    }

    static void Main(string[] args)
    {
        int a = 2, b = 5, c = 2;
        double rootValue, x1, x2;
        rootValue = (double)Math.Sqrt(b * b - 4 * a * c);
        x1 = (-b + rootValue) / (2 * a);
        x2 = (-b - rootValue) / (2 * a);
        Console.WriteLine("a= {0}, b= {1}, c= {2}, x1= {3}, x2= {4}", a, b, c, x1, x2);
    }

    static void Main(string[] args)
    {
        Console.WriteLine("----각 자료형의 크기 구하기----\n");
        Console.WriteLine("부호있는 8비트 정수형 sbyte = {0} byte", sizeof(sbyte));
        Console.WriteLine("부호없는 8비트 정수형 byte = {0} byte", sizeof(byte));
        Console.WriteLine("유니코드 16비트 문자형 char = {0} byte", sizeof(char));
        Console.WriteLine("부호있는 16비트 정수형 short = {0} byte", sizeof(short));
        Console.WriteLine("부호없는 16비트 정수형 ushort = {0} byte", sizeof(ushort));
        Console.WriteLine("부호있는 32비트 정수형 int = {0} byte", sizeof(int));
        Console.WriteLine("부호없는 32비트 정수형 uint = {0} byte", sizeof(uint));
        Console.WriteLine("부호있는 64비트 정수형 long = {0} byte", sizeof(long));
        Console.WriteLine("부호없는 64비트 정수형 ulong = {0} byte", sizeof(ulong));
        Console.WriteLine("32비트 실수형 float = {0} byte", sizeof(float));
        Console.WriteLine("64비트 실수형 double = {0} byte", sizeof(double));
        Console.WriteLine("불리언형 8비트 논리형 bool = {0} byte", sizeof(bool));
        Console.WriteLine("16바이트 십진형 decimal = {0} byte", sizeof(decimal));
    }

    static void Main(string[] args)
    {
        char ch;
        int i;
        Console.Write("임의의 문자 입력 : ");
        ch = (char)(Console.Read());
        i = (int)ch;
        Console.WriteLine("입력된 문자= \'{0}\', ASCII코드 값= {1}", ch, i);
    }

    static void Main(string[] args)
    {
        bool boolA, boolB;
        int inputX, inputY;
        Console.Write("첫번째 정수 입력 : ");
        inputX = Int32.Parse(Console.ReadLine());
        Console.Write("두번째 정수 입력 : ");
        inputY = Int32.Parse(Console.ReadLine());
        boolA = inputX > inputY;
        Console.WriteLine("{0} > {1} = {2}", inputX, inputY, boolA);
        boolB = inputX < inputY;
        Console.WriteLine("{0} < {1} = {2}", inputX, inputY, boolB);
    }

    enum Vecicles { bycle, autoBycle, car, bus, truck, airPlane };
    static void Main(string[] args)
    {
        int vechilesOrder = (int)Vecicles.bus;
        Console.WriteLine("열거형에서 bycle=0, autoBycle=1,...,airPlane=5");
        Console.WriteLine("열거형에서 bus의 순서= {0}", vechilesOrder);
    }

public struct Vechiles
{
    public string kinds; // 자동차의 종류
    public int wheels; // 바퀴의 개수
    public int persons; // 승차인원
    public string colors; // 색상
                            // 생성자 (각 멤버 변수 초기화)
    public Vechiles(string kinds, int wheels, int persons, string colors)
    {
        this.kinds = kinds;
        this.wheels = wheels;
        this.persons = persons;
        this.colors = colors;
    }
}
class Program
{
    static void Main(string[] args)
    {
        Vechiles vc = new Vechiles();
        vc.kinds = "승용차";
        vc.wheels = 4;
        vc.persons = 5;
        vc.colors = "빨간색";
        Console.WriteLine("차종= {0}, 바퀴개수= {1}개, 승차인원= {2}명, 색상= {3}", vc.kinds, vc.wheels, vc.persons, vc.colors);
    }
}

    static void Main(string[] args)
    {
        string str1, str2, str3;
        str1 = "C# 프로그래밍";
        str2 = "MSVS 2003";
        str3 = str1 + str2;
        Console.WriteLine("\"{0}\" : 문자열 길이={1}", str1, str1.Length);
        Console.WriteLine("\"{0}\" : 문자열 길이={1}", str2, str2.Length);
        Console.WriteLine("\n두 문자열을 비교한 결과={0}", string.Equals(str1, str2));
    }

    static void Main(string[] args)
    {
        int[] intArray = { 10, 20, 30, 40, 50 };
        int[][] multiArray = { new int[] { 1, 2, 3, 4 }, new int[] { 3, 4, 5, 6 }, new int[] { 4, 3, 2, 1 } };
        int sum = 0;
        Console.WriteLine("====1차원 배열====\n");
        foreach (int arr in intArray)
            Console.Write(arr + "\t");
        for (int i = 0; i < intArray.Length; i++)
            sum += intArray[i];
        Console.WriteLine();
        Console.WriteLine("1차원 배열의 합={0}\n", sum);

        Console.WriteLine("====다차원 배열====\n");
        for (int i = 0; i < multiArray.Length; i++)
        {
            int twoSum = 0;
            for (int j = 0; j < multiArray[i].Length; j++)
            {
                twoSum += multiArray[i][j];
                Console.Write(" " + multiArray[i][j] + " ");
            }
            Console.WriteLine(" : [{0}] 행의 합={1}", i, twoSum);
        }
    }

    static void Main(string[] args)
    {
        object intType = 123;
        object doubleType = 45.67;
        object boolType = (100 < 200) && (3 > 5);
        object charType = "정";
        object stringType = "지성";
        Console.WriteLine("====object형이 모든 자료형을 포함한 경우====\n");
        Console.WriteLine("intTtpe = {0,6} : 정수형 형식={1,7}", intType.ToString(), intType.GetType());
        Console.WriteLine("doubleType = {0,6} : 실수형 형식={1,7}", doubleType.ToString(), doubleType.GetType());
        Console.WriteLine("boolType = {0,6} : 불린형 형식={1,7}", boolType.ToString(), boolType.GetType());
        Console.WriteLine("charType = {0,6} : 문자형 형식={1,7}", charType.ToString(), charType.GetType());
        Console.WriteLine("stringType = {0,6} : 문자열형 형식={1,7}", stringType.ToString(), stringType.GetType());
    }

    static void Main(string[] args)
    {
        short s;
        int i = 32768;
        double d = 34.56;
        decimal decimalType;
        s = (short)i;
        Console.WriteLine("====명시적 형 변환====\n");
        Console.WriteLine("명시적 형 변환 : int형을 short형으로 명시적으로 Casting할 경우s의 값 ={0}", s);
        i = (int)d;
        Console.WriteLine("명시적 형 변환 : double형 \"34.56\"을 int형으로 명시적으로 Casting할 경우 i의 값 ={0}", i);
            
        s = 32767;
        i = s;
        decimalType = i * 1000;
        Console.WriteLine("\n====묵시적 형 변환====\n");
        Console.WriteLine("묵시적 형 변환 : int형이 decimal형으로 자동 Casting될 경우 decimalType의 값 ={0:N}", decimalType);
        Console.WriteLine("묵시적 형 변환 : short이 int형으로 자동 Casting될 경우 i의 값 ={0}", i);
        d = i;
        Console.WriteLine("묵시적 형 변환 : int형이 double형으로 자동 Casting될 경우 d의 값 ={0:F}", d);
    }

    static void Main(string[] args)
    {
        short i = 32767;
        Console.WriteLine("short형 값={0}", i);
        i = (short)(i + 1);
        Console.WriteLine("\n====short형 일때 Overflow가 발생한 경우====\n");
        Console.WriteLine("\"32767 + 1\"의 결과= {0}", i);
            
        i = 32767;
        int x = i + 1;
        Console.WriteLine("\n====short형을 int형으로 선언한 경우====\n");
        Console.WriteLine("\"32767 + 1\"의 결과= {0}", x);
    }

    static void Main(string[] args)
    {
        int score;
        char grade;
        Console.WriteLine("Switch문");
        Console.Write("점수 입력 : ");
        score = Int32.Parse(Console.ReadLine());
        switch (score / 10)
        {
            case 10:
            case 9: grade = 'A'; break;
            case 8: grade = 'B'; break;
            case 7: grade = 'C'; break;
            case 6: grade = 'D'; break;
            default: grade = 'F'; break;
        }
        Console.WriteLine("{0}점은 {1}학점입니다.", score, grade);
    }
*/