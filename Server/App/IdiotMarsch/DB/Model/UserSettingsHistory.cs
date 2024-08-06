using IdiotMarsch.Db.Attributes;
using System;

namespace IdiotMarsch.Db.Model
{
    [TableName("h_user_settings")]
    public class UserSettingsHistory : EntityHistory
    {
        [ColumnName("userid")]
        public Guid UserId { get; set; }

        [ColumnName("leaf_only")]
        public bool LeafOnly { get; set; }

        [ColumnName("default_reserve_value")]
        public decimal DefaultReserveValue { get; set; }       
    }
}
