##Задача 9. Алгоритм сжатия данных Хаффмана(15 баллов)
###
Реализуйте алгоритм построения оптимального префиксного кода Хаффмана. При помощи алгоритма реализуйте две функции для создания архива из одного файла и извлечения файла из архива.


// Метод архивирует данные из потока original
void Encode(IInputStream& original, IOutputStream& compressed);
// Метод восстанавливает оригинальные данные
void Decode(IInputStream& compressed, IOutputStream& original);
 где:
typedef unsigned char byte;

struct IInputStream {
	// Возвращает false, если поток закончился
	bool Read(byte& value) = 0;
};

struct IOutputStream {
	void Write(byte value) = 0;
};

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит скоринг зависящий от соотношения размера сжатого файла и исходного.
