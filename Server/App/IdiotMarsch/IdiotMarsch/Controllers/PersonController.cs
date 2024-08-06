using IdiotMarsch.Contract.Filters;
using IdiotMarsch.Contract.Interfaces;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using Serilog.Core;
using System.Threading;
using System;
using System.Threading.Tasks;
using IdiotMarsch.Contract.Models;

namespace IdiotMarsch.Controllers
{
    [ApiController]
    [Route("api/person")]
    [Authorize]
    [Produces("application/json")]
    public class PersonController: Controller
    {
        private IPersonDataService _personDataService;
        private ILogger<PersonController> _logger;

        public PersonController(ILogger<PersonController> logger, IPersonDataService personDataService) 
        {
            _personDataService = personDataService;
            _logger = logger;
        }

        [HttpGet("getlist")]
        public async Task<IActionResult> GetList(PersonFilter filter)
        {
            try
            {
                var userId = Guid.Parse(User.Identity.Name);
                var source = new CancellationTokenSource(30000);
                var result = await _personDataService.GetAsync(filter, userId, source.Token);
                if (result.IsSuccess)
                    return Ok(result.Value);

                return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Ошибка при получении списка характеристик");
                return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
            }
        }

        //[HttpPost("update")]
        //public async Task<IActionResult> UpdateAsync(PersonsUpdater updater)
        //{
        //    try
        //    {
        //        var userId = Guid.Parse(User.Identity.Name);
        //        var source = new CancellationTokenSource(30000);
        //        var result = await _personDataService.UpdateAsync(updater, userId, source.Token);
        //        if (result.IsSuccess)
        //            return Ok(result.Value);

        //        return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
        //    }
        //    catch (Exception ex)
        //    {
        //        _logger.LogError(ex, "Ошибка при обновлении характеристики");
        //        return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
        //    }
        //}

        //[HttpGet("get")]
        //public async Task<IActionResult> Get(Guid id)
        //{
        //    try
        //    {
        //        var userId = Guid.Parse(User.Identity.Name);
        //        var source = new CancellationTokenSource(30000);
        //        var result = await _personDataService.GetAsync(id, userId, source.Token);
        //        if (result.IsSuccess)
        //            return Ok(result.Value);

        //        return StatusCode(StatusCodes.Status500InternalServerError, result.Message);
        //    }
        //    catch (Exception ex)
        //    {
        //        _logger.LogError(ex, "Ошибка при получении характеристики");
        //        return StatusCode(StatusCodes.Status500InternalServerError, ex.Message);
        //    }
        //}
    }
}
