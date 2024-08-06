using Microsoft.Extensions.DependencyInjection;
using System.Diagnostics.Contracts;

namespace Service
{
    public static class DataServiceExtension
    {
        public static IServiceCollection AddDataServices(this IServiceCollection services)
        {
            //services.AddScoped<IUserDataService, UserDataService>();
            //services.AddScoped<IUserHistoryDataService, UserHistoryDataService>();            
            //services.AddScoped<IAuthService, AuthService>();

            return services;
        }

       
    }
}
