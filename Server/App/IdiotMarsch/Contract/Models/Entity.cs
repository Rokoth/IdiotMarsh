using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Interfaces;
using System;

namespace IdiotMarsch.Contract.Models
{
    public class Entity : IEntity
    {
        public Guid Id { get; set; }
    }
}
