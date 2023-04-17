
void removeOdds(vector<int>& v)
{
    // get an iterator and check if it's odd
    // then delete that
    // once it's at the end then leave the function
    
    for (int i = 0; i < v.size(); i++)
    {
        if ((v[i] % 2) == 1)
        {
            vector<int>::iterator it;
            it = v.begin();
            for (int j = 0; j < i; j++)
                it++;
            v.erase(it);
            i--;
        }
    }
}
