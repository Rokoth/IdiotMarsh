﻿namespace IdiotMarsch.Db.Model
{
    public interface IIdentity
    {
        string Login { get; set; }
        byte[] Password { get; set; }
    }
}