using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Models;

namespace IdiotMarsch.Contract.Interfaces
{
    public interface IFilter<T> where T : Entity
    {
        /// <summary>
        /// Страница
        /// </summary>
        int? Page { get; }
        /// <summary>
        /// Размер
        /// </summary>
        int? Size { get; }
        /// <summary>
        /// Поле сортировки
        /// </summary>
        string Sort { get; }
    }
}
