using IdiotMarsch.Db.Attributes;
using System;

namespace IdiotMarsch.Db.Model
{
    [TableName("user")]
    public class User : Entity, IIdentity
    {
        [ColumnName("name")]
        public string Name { get; set; }
        [ColumnName("description")]
        public string Description { get; set; }
        [ColumnName("email")]
        public string Email { get; set; }
        [ColumnName("login")]
        public string Login { get; set; }
        [ColumnName("password")]
        public byte[] Password { get; set; }
        
        [ColumnName("last_login_date")]
        public DateTimeOffset LastLoginDate { get; set; }
    }
}