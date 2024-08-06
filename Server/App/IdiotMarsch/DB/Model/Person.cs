using IdiotMarsch.Db.Attributes;
using System;

namespace IdiotMarsch.Db.Model
{
    [TableName("person")]
    public class Person : Entity
    {
        [ColumnName("name")]
        public string Name { get; set; }

        [ColumnName("user_id")]
        public Guid UserId { get; set; }
        
    }
}