

void listAll(const File* f, string path)  // two-parameter overload
{
    path += ("/" + f->name());
    cout << path << endl;
    
    if (f->files() == nullptr)
        return;
    
    for (int i = 0; i < f->files()->size(); i++)
    {
        listAll(f->files()->at(i), path);
    }
}
