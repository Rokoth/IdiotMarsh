using System.Collections.Generic;

namespace IdiotMarsch.Contract.Models
{
    public class EntityList<T> where T : Entity
    {
        public EntityList(List<T> entities, int allCount, int page, int size)
        {
            Entities = entities;
            AllCount = allCount;
            Page = page;
            if (size == 0)
            {
                Size = 1;
            }
            else
            {
                Size = size;
            }

        }

        public List<T> Entities { get; private set; }

        public int AllCount { get; private set; }

        public int Page { get; private set; }

        public int Size { get; private set; }

        public int PageCount
        {
            get
            {
                var div = AllCount % Size;
                var pages = AllCount / Size;
                if (div > 0) pages++;
                return pages;
            }
        }

    }
}
