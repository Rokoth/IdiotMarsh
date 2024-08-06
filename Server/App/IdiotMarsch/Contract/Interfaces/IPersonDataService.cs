using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Models;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace IdiotMarsch.Contract.Interfaces
{
    public interface IPersonDataService
    {
        //Task<Response<Person>> GetAsync(Guid id, Guid userId, CancellationToken token);
        Task<Response<EntityList<Person>>> GetAsync(PersonFilter filter, Guid userId, CancellationToken token);
        //Task<Response<Person>> UpdateAsync(PersonUpdater model, Guid userId, CancellationToken token);
    }
}
