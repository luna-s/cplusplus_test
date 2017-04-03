#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;

namespace lunas {

#define MAX_THRESHOLD 5000
#define MAX_FILENAME 512

typedef struct _Alloc
{
	unsigned int size;
	void *ptr;
	char file[512];
	int line;
} Alloc;

typedef std::vector<Alloc> AllocList;
typedef std::vector<Alloc>::iterator AllocIter;

class HeapManager
{
private:
	unsigned int total_alloc_size_;
	unsigned int new_count_;
	unsigned int del_count_;
	unsigned int cur_count_;
	unsigned int new_failed_count_;
	unsigned int del_failed_count_;

	AllocList alloc_list_;

public:
	static HeapManager sHeapManager;



public:
	HeapManager()
	{
		alloc_list_.reserve(MAX_THRESHOLD);
	}
	~HeapManager() {}

public:
	void setOwner(const char *file, const unsigned int line);

	void *add(size_t size, const char *file, const int line)
	{
		mtx.lock();

		void *ptr = malloc(size);
		if (!ptr) {
			std::cout << "Heap memory is shortage" << std::endl;
			std::cout << size << file << line << std::endl;
			new_failed_count_ += 1;
			mtx.unlock();
			return NULL;
		}

		total_alloc_size_ += size;
		new_count_ += 1;
		cur_count_ += 1;

		Alloc alloc;
		alloc.ptr = ptr;
		alloc.size = size;
		alloc.line = line;
		//std::strcpy(alloc.file, file);
		strcpy_s(alloc.file, sizeof(alloc.file), file);
		alloc_list_.push_back(alloc);

		mtx.unlock();
		return ptr;
	}

	void remove(void *ptr, const char *file, const int line)
	{
		mtx.lock();

		if (!ptr) {
			std::cout << "NULL NULL NULL ptr " << std::endl;
			std::cout << file << line << std::endl;
			std::cout << std::endl;
			mtx.unlock();
			return;
		}

		Alloc alloc;
		for (int i = 0; i < alloc_list_.size(); ++i) {
			alloc = alloc_list_[i];
			if (alloc.ptr == ptr) {
				total_alloc_size_ -= alloc.size;
				del_count_ += 1;
				cur_count_ -= 1;
				alloc_list_.erase(alloc_list_.begin() + i);
				goto FREEFREE;
			}
		}

		del_failed_count_ += 1;
		std::cout << ptr << "i dont know ptr " ;
		std::cout << file << line << std::endl;
		std::cout << std::endl;
		
	FREEFREE:
		free(ptr);

		mtx.unlock();
	}

	void printInfo()
	{
		mtx.lock();
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "total alloc size : " << total_alloc_size_ << std::endl;
		std::cout << "new count :" << new_count_ << std::endl;
		std::cout << "delete count : " << del_count_ << std::endl;
		std::cout << "current new count : " << cur_count_ << std::endl;
		std::cout << "failed new count : " << new_failed_count_ << std::endl;
		std::cout << "failed delete count : " << del_failed_count_ << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << std::endl;
		mtx.unlock();
	}

	void printRemain()
	{
		mtx.lock();
		Alloc alloc;
		std::cout << "---REMAINS----------------------------------------" << std::endl;
		std::cout << "ADDRESS" << "\t\t" << "SIZE" << "\t" << "LINE" << "\t" << "FILE" << std::endl;
		for (int i = 0; i < alloc_list_.size(); ++i) {
			alloc = alloc_list_[i];
			std::cout << "0x" << alloc.ptr << "\t" << alloc.size << "\t" << alloc.line << "\t" << alloc.file << std::endl;
		}
		std::cout << "---END----------------------------------------" << std::endl;
		std::cout << std::endl;
		mtx.unlock();
	}
};

static HeapManager g_heap_manager;
}


#if 0
static const char *g_file;
static int g_line;

void *operator new(size_t size, const char *file, const int line)
{
	//	std::cout << "new " << size << std::endl;
	
	return lunas::g_heap_manager.add(size, file, line);
}

void *operator new[](size_t size, const char *file, const int line)
{
	return operator new(size, file, line);
}

void operator delete(void *addr) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	lunas::g_heap_manager.remove(addr, g_file, g_line);
}

void operator delete(void *addr, const char *file, const int line) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	lunas::g_heap_manager.remove(addr, g_file, g_line);
}

void operator delete[](void *addr) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	return operator delete(addr, g_file, g_line);
}

void operator delete[](void *addr, const char *file, const int line) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	return operator delete(addr, g_file, g_line);
}

void deletep(const char *file, const int line)
{
	g_file = file;
	g_line = line;
}

#define new new(__FILE__, __LINE__)
#define delete deletep(__FILE__, __LINE__), delete

#else

static const char *g_file;
static int g_line;

void *operator new(size_t size, const char *file, const int line)
{
	//	std::cout << "new " << size << std::endl;

	return ::lunas::g_heap_manager.add(size, file, line);
}

void *operator new[](size_t size, const char *file, const int line)
{
	return operator new(size, file, line);
}

void operator delete(void *addr) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	::lunas::g_heap_manager.remove(addr, g_file, g_line);
}

void operator delete(void *addr, const char *file, const int line) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	lunas::g_heap_manager.remove(addr, g_file, g_line);
}

void operator delete[](void *addr) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	return operator delete(addr, g_file, g_line);
}

void operator delete[](void *addr, const char *file, const int line) throw()
{
	//const char *file = g_file;
	//const int line = g_line;
	return operator delete(addr, g_file, g_line);
}

void deletep(const char *file, const int line)
{
	g_file = file;
	g_line = line;
}


#define new new(__FILE__, __LINE__)
#define delete deletep(__FILE__, __LINE__), delete

//#define new		(lunas::g_heap_manager.setOwner(__FILE__, __LINE__), false) ? NULL : new
//#define delete	(lunas::g_heap_manager.setOwner(__FILE__, __LINE__), false) ? lunas::g_heap_manager.setOwner("", 0) : delete

#endif

