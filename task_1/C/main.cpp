#include <iostream>
#include <string>

using namespace std;

struct entrant
{
    string name = "";
    string surname = "";
    int score = 0;
};

entrant* merger(entrant* arr_1, entrant* arr_2, int size_1, int size_2)
{
    int size_ans = size_1 + size_2;
    entrant* ans = new entrant[size_ans];
    for (int it_1 = 0, it_2 = 0; it_1 + it_2 < size_ans;)
    {
        if ((it_1 < size_1) && (it_2 < size_2))
        {
            (arr_1[it_1].score >= arr_2[it_2].score) ? ((ans[it_1 + it_2] = arr_1[it_1]), (it_1++)) : ((ans[it_1 + it_2] = arr_2[it_2]) , (it_2++));
        }
        else
        {
            for (it_1; it_1 < size_1; ++it_1)
            {
                ans[it_1 + it_2] = arr_1[it_1];
            }
            for (it_2; it_2 < size_2; ++it_2)
            {
                ans[it_1 + it_2] = arr_2[it_2];
            }
        }
    }
    arr_1 = new entrant[size_ans];
    for (int i = 0; i < size_ans; ++i)
    {
        arr_1[i] = ans[i];
    }
    delete[] ans;
    return arr_1;
}

entrant* merge_sort(entrant* arr, int left, int right)
{
    if (left == right - 1)
    {
        return &arr[left];
    }
    else
    {
        int mid = (left + right) / 2;
        entrant* arr_left = merge_sort(arr, left, mid);
        entrant* arr_right = merge_sort(arr, mid, right);
        return merger(arr_left, arr_right, mid - left, right - mid);
    }
}

int main()
{
    int N = 0;
    cin >> N;
    entrant* arr = new entrant[N];
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i].name >> arr[i].surname >> arr[i].score;
        int a = 0;
        cin >> a;
        arr[i].score += a;
        cin >> a;
        arr[i].score += a;
    }
    entrant* ans = merge_sort(arr, 0, N);
    for (int i = 0; i < N; ++i)
    {
        cout << ans[i].name << " " << ans[i].surname << "\n";
    }
    delete[] arr;
    delete[] ans;
    return 0;
}
