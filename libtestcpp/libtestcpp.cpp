// libtestcpp.cpp :

#include <iostream>

#define SDL_MAIN_HANDLED

#include "SDL2/SDL.h"
#include<random>
#include<ranges>
#include <algorithm>

void draw_state(std::vector<int>& v,
    SDL_Renderer* renderer,
    unsigned int red,
    unsigned int blue);


void quick_sort(std::vector<int>& v, unsigned int left, unsigned int right,SDL_Renderer* renderer) {
	unsigned int i = left, j = right;
	int tmp;
	int pivot = v[(left + right) / 2];

	/* partition */
    while (i <= j) {
		while (v[i] < pivot)
			i++;
		while (v[j] > pivot)
			j--;
        if (i <= j) {
			std::swap(v[i], v[j]);
			i++;
			j--;
		}
	};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    draw_state(v, renderer, i, j);

    SDL_RenderPresent(renderer);
    SDL_Delay(50);

	/* recursion */
	if (left < j)
		quick_sort(v, left, j, renderer);
	if (i < right)
		quick_sort(v, i, right, renderer);
}

void bubbleSort(std::vector<int>& v, SDL_Renderer* renderer) {
	for(unsigned int i = 0; i < v.size(); i++)
    {
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                std::swap(v[j], v[i]);
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(v, renderer, i, j);

            SDL_RenderPresent(renderer);
            SDL_Delay(5);
        }
    
}
}




void draw_state(std::vector<int>& v,
    SDL_Renderer* renderer,
    unsigned int red,
    unsigned int blue) {

    int index = 0;
    for (int i : v) {
        if (index == red) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);            
        }
        else if (index == blue) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index++;

    }
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::uniform_int_distribution d(1, 99);
    std::vector<int> v;

    for (int i = 0; i < 100; i++)
    {
		v.push_back(d(rd));
    }   

    for (int i : v)
    {
        std::cout << i << " " ;
	}

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(
        100 * 10, 100 * 10, 0,
        &window, &renderer);
    
    SDL_RenderSetScale(renderer,10,10);
    

    //bubble sort
    //bubbleSort(v, renderer);

    //quick sort
    quick_sort(v, 0, v.size() - 1, renderer);



    return 0;

}
