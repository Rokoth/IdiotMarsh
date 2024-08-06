using IdiotMarsch.Contract.Models;

namespace IdiotMarsch.Contract.Filters
{
    public class PersonFilter : Filter<Person>
    {
        public PersonFilter(int? size, int? page, string sort, string name) : base(size, page, sort)
        {
            Name = name;
        }
        /// <summary>
        /// User Name
        /// </summary>
        public string Name { get; }
    }



}
