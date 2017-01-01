#pragma once
#ifndef QUEUE_H
#define QUEUE_H

template <typename QU>
class queueV {
private:
	unsigned int size;
	struct list {
		QU value;
		list *ptr;
	};
	list *first, *last;

public:
	//����������� �������.
	queueV()
	{
		size = 0;
		list *lst;
		lst = new list;
		lst->ptr = nullptr;
		first = lst;
		last = lst;
	}

	//���������� �������.
	~queueV()
	{
		if (size > 0) {
			list *temp;
			while (first->ptr != nullptr) {
				temp = first;
				first = first->ptr;
				delete temp;
			}
			delete first;
		}
		else
			delete first;
		size = 0;
	}

	//���������� �������� � �������.
	void push(QU value)
	{
		if (size == 0) {
			if (first != nullptr) {
				first->value = value;
				last = first;
			}
			else {
				list *temp;
				temp = new list;
				temp->value = value;
				temp->ptr = nullptr;
				first = temp;
				last = temp;
			}
		}
		else {
			list *temp, *temp2;
			temp = new list;
			temp2 = last->ptr;
			last->ptr = temp;
			temp->value = value;
			temp->ptr = temp2;
			last = temp;
		}
		size++;
	}

	//���������� �������� �� �������.
	QU pop()
	{
		QU result;
		if (size > 0) {
			list *temp;
			temp = first->ptr;
			result = first->value;
			delete first;
			first = temp;
			size--;
		}
		else
			throw "queueV<>:: empty queue!";
		return result;
	}


	//����� �������.
	void print() {
		list *temp;
		temp = first;
		for (unsigned int i = 0; i < size; i++) {
			std::cout << temp->value << " ";
			temp = temp->ptr;
		}
		std::cout << "\n";
	}

	//��������� ������� �������.
	unsigned int getSize()
	{
		return size;
	}

	//�������� ������� �������.
	bool empty()
	{
		return (size == 0);
	}

	//������� �������.
	void clear()
	{
		if (size > 0) {
			list *temp;
			while (first->ptr != nullptr) {
				temp = first;
				first = first->ptr;
				delete temp;
			}
			delete first;
		}
		else
			delete first;
		size = 0;
		first = new list;
		first->ptr = nullptr;
		last = first;
	}
};

#endif /* QUEUE_H */