using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Models;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace IdiotMarsch.Contract.Interfaces
{
    public interface ICharacteristicDataService
    {
        Task<Response<Characteristics>> GetAsync(Guid id, Guid userId, CancellationToken token);
        Task<Response<EntityList<Characteristics>>> GetAsync(CharacteristicsFilter filter, Guid userId, CancellationToken token);
        Task<Response<Characteristics>> UpdateAsync(CharacteristicsUpdater model, Guid userId, CancellationToken token);
    }
}
