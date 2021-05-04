#include <vector>
#include <iostream>
#include <utility>
using namespace std;

vector<pair<int, pair<int, int> > > moves; 
void move(int disk, int source_rod, int destination_rod){
	moves.push_back(make_pair(disk, make_pair(source_rod, destination_rod)));
}

void print_moves(){
	//Uncomment this code block to print moves. Beware, it could be a lot of prints!
	/*
	for(auto move: moves){
		cout << "Move disk " << move.first << " from rod " << move.second.first 
		     << " to rod " << move.second.second << endl;
	*/
	cout << "Made a total of " << moves.size() << " moves " << endl;
}

void solve(int n, int source_rod, int destination_rod, int helper_rod)
{
    if (n == 1)
    {
	//Base case: Only one disk, so move it from source to destination
	move(1, source_rod, destination_rod);
        return;
    }
    //Move n-1 disks from source to the helper rod
    solve(n - 1, source_rod, helper_rod, destination_rod);
    //Move the nth disk from source to destination
    move(n, source_rod, destination_rod);
    //Move the remaining n-1 disks which were on helper rod to destination
    solve(n - 1, helper_rod, destination_rod, source_rod);
}
 
int main()
{
    int disks = 15;
    solve(disks, 1, 3, 2); // 1, 2 and 3 are the rods. 
    print_moves();
    return 0;
}
 
