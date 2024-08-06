using System.Threading.Tasks;

namespace IdiotMarsch.InternalDeployer
{
    public interface IDeployService
    {
        Task Deploy(int? num = null);
    }
}
